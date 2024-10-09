#include <Arduino.h>
#include <WiFi.h>
#include "TaskHandler.h"
#include "Config.h"
#include "DataStorage.h"
#include "Communik.h"
#include "InstrumentsControl.h"
#include "VisuControl.h"
#include "Troubleshooter.h"
#include "config.h"

static void application_task(void *param)
{
    // delegate onto the application
    TaskHandler *taskHandler = reinterpret_cast<TaskHandler *>(param);
    taskHandler->loop();
}

TaskHandler::TaskHandler()
{
    m_output_buffer = new OutputBuffer(300 * 16);

    #ifdef USE_ESP_NOW
    m_transport = new EspNowTransport(m_output_buffer,ESP_NOW_WIFI_CHANNEL);
    #else
    m_transport = new UdpTransport(m_output_buffer);
    #endif

    m_transport->set_header(TRANSPORT_HEADER_SIZE,transport_header);
}

void TaskHandler::begin()
{
  // show a flashing indicator that we are trying to connect
  m_indicator_led->set_default_color(0);
  m_indicator_led->set_is_flashing(true, 0xff0000);
  m_indicator_led->begin();

  Serial.print("My IDF Version is: ");
  Serial.println(esp_get_idf_version());

  // bring up WiFi
  WiFi.mode(WIFI_STA);
#ifndef USE_ESP_NOW
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // this has a dramatic effect on packet RTT
  WiFi.setSleep(WIFI_PS_NONE);
  Serial.print("My IP Address is: ");
  Serial.println(WiFi.localIP());
#else
  // but don't connect if we're using ESP NOW
  WiFi.disconnect();
#endif
  Serial.print("My MAC Address is: ");
  Serial.println(WiFi.macAddress());
  // do any setup of the transport
  m_transport->begin();
  // connected so show a solid green light
  m_indicator_led->set_default_color(0x00ff00);
  m_indicator_led->set_is_flashing(false, 0x00ff00);
  // setup the transmit button
  pinMode(GPIO_TRANSMIT_BUTTON, INPUT_PULLDOWN);
  // start off with i2S output running
  m_output->start(SAMPLE_RATE);
  // start the main task for the application
  TaskHandle_t task_handle;
  xTaskCreate(application_task, "application_task", 8192, this, 1, &task_handle);
}

// application task - coordinates everything
void Application::loop()
{
  int16_t *samples = reinterpret_cast<int16_t *>(malloc(sizeof(int16_t) * 128));
  // continue forever
  while (true)
  {
    // do we need to start transmitting?
    if (digitalRead(GPIO_TRANSMIT_BUTTON))
    {
      Serial.println("Started transmitting");
      m_indicator_led->set_is_flashing(true, 0xff0000);
      // stop the output as we're switching into transmit mode
      m_output->stop();
      // start the input to get samples from the microphone
      m_input->start();
      // transmit for at least 1 second or while the button is pushed
      unsigned long start_time = millis();
      while (millis() - start_time < 1000 || digitalRead(GPIO_TRANSMIT_BUTTON))
      {
        // read samples from the microphone
        int samples_read = m_input->read(samples, 128);
        // and send them over the transport
        for (int i = 0; i < samples_read; i++)
        {
          m_transport->add_sample(samples[i]);
        }
      }
      m_transport->flush();
      // finished transmitting stop the input and start the output
      Serial.println("Finished transmitting");
      m_indicator_led->set_is_flashing(false, 0xff0000);
      m_input->stop();
      m_output->start(SAMPLE_RATE);
    }
    // while the transmit button is not pushed and 1 second has not elapsed
    Serial.println("Started Receiving");
    if (I2S_SPEAKER_SD_PIN != -1)
    {
      digitalWrite(I2S_SPEAKER_SD_PIN, HIGH);
    }
    unsigned long start_time = millis();
    while (millis() - start_time < 1000 || !digitalRead(GPIO_TRANSMIT_BUTTON))
    {
      // read from the output buffer (which should be getting filled by the transport)
      m_output_buffer->remove_samples(samples, 128);
      // and send the samples to the speaker
      m_output->write(samples, 128);
    }
    if (I2S_SPEAKER_SD_PIN != -1)
    {
      digitalWrite(I2S_SPEAKER_SD_PIN, LOW);
    }
    Serial.println("Finished Receiving");
  }
}