#ifndef PAWS_LIB_BOARDLED_H
#define PAWS_LIB_BOARDLED_H


class GenericDevBoardIndicatorLed : public IndicatorLed {
    protected:
        void set_led_rgb(uint32_t color);
        bool m_is_flashing = false;
        uint32_t m_default_color = 0;
        uint32_t m_flash_color = 0;

    public:
        GenericDevBoardIndicatorLed();
};

#endif // PAWS_LIB_BOARDLED_H

/*
private:
  bool m_is_flashing = false;
  uint32_t m_default_color = 0;
  uint32_t m_flash_color = 0;

protected:
  virtual void set_led_rgb(uint32_t color) = 0;

public:
  void begin();
  void set_is_flashing(bool is_flashing, uint32_t flash_color);
  void set_default_color(uint32_t color);

  friend void update_indicator_task(void *param);
*/