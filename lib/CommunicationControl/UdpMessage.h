#ifndef PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
#define PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
#include <Arduino.h>

namespace Communication
{
    template <typename Payload>
    class UdpMessage
    {
    public:
        // Enum for message types
        enum MessageType
        {
            DATA,
            CMD,
            STAT,
            ERROR
        };
        enum CommandPayloads : uint8_t
        {
            START_TRANSMISSION = 0, // Signal to start data transmission
            STOP_TRANSMISSION = 1,  // Signal to stop data transmission
            SENSOR_DATA = 2,        // Generic sensor data _payload
            HEARTBEAT = 3,          // Keep-alive signal between devices
            CONFIG_UPDATE = 4,      // Configuration update from server to client
            ACKNOWLEDGMENT = 5,     // Acknowledgment of received data
            ERROR_MESSAGE = 6,      // Error report from client or server
            REQUEST_STATUS = 7,     // Request status of a client
            STATUS_RESPONSE = 8,    // Response with status information
            CONNECTION_LOST = 9,    // Notification of a lost connection
            DATA_END = 10,          // Signal that all data has been sent
            CALIBRATION_DATA = 11,  // Data for calibrating sensors
            RESET_DEVICE = 12,      // Signal to reset a client or server
            TEST_SIGNAL = 13        // Signal for testing communication
        };
        enum StatusPayloads
        {
            STARTED_TRANSMISSION = 20,        // Indicates transmission has started
            STOPPED_TRANSMISSION = 21,        // Indicates transmission has stopped
            SENSOR_DATA_RECEIVED = 22,        // Acknowledges receipt of sensor data
            HEARTBEAT_RECEIVED = 23,          // Acknowledges heartbeat signal
            CONFIG_UPDATED = 24,              // Confirms successful configuration update
            ACK_RECEIVED = 25,                // Acknowledges a received acknowledgment
            ERROR_DETECTED = 26,              // Indicates an error was detected
            STATUS_OK = 27,                   // General status indicating "all is well"
            CONNECTION_ESTABLISHED = 28,      // Confirms a successful connection
            CONNECTION_WITH_SERVER_LOST = 29, // Indicates the connection was lost
            DATA_TRANSMISSION_DONE = 30,      // Confirms that data transmission is complete
            SENSOR_CALIBRATED = 31,           // Indicates successful sensor calibration
            DEVICE_RESET_DONE = 32,           // Confirms device reset was successful
            TEST_SIGNAL_OK = 33               // Confirms the test signal was received successfully
        };
        enum ErrorPayloads
        {
            INVALID_COMMAND = 40,        // Received an unrecognized or unsupported command
            TRANSMISSION_FAILED = 41,    // Failed to send or receive data
            SENSOR_ERROR = 42,           // Problem with sensor operation or data
            CONFIG_ERROR = 43,           // Failed to apply configuration settings
            CONNECTION_TIMEOUT = 44,     // Lost connection due to a timeout
            ACK_TIMEOUT = 45,            // Did not receive acknowledgment in time
            MEMORY_ALLOCATION_FAIL = 46, // Failed to allocate memory
            UNSUPPORTED_PAYLOAD = 47,    // Payload _type not recognized or supported
            PERMISSION_DENIED = 48,      // Command or action not permitted
            DEVICE_BUSY = 49,            // Device is currently busy with another operation
            RESET_FAILED = 50,           // Failed to reset the device
            CALIBRATION_FAILED = 51,     // Sensor calibration failed
            DATA_OVERFLOW = 52,          // Received data exceeds buffer capacity
            DATA_CORRUPTED = 53,         // Received data is corrupted
            UNKNOWN_ERROR = 54           // Catch-all for unexpected errors
        };

        // Constructor
        UdpMessage() {};

        UdpMessage(MessageType _type, Payload newPayload)
            : _type(_type)
        {
            _payload = newPayload;
            _timestamp = millis(); // Timestamp in milliseconds since program start
        }

        /*
        UdpMessage(MessageType _type, char *newHostID, char *newClientID, Payload newPayload)
            : _type(_type)
        {
            _hostID = newHostID;
            _clientID = newClientID;
            _payload = newPayload;
            _timestamp = millis(); // Timestamp in milliseconds since program start
        };
        */

        // Setters
        void setType(MessageType newType) { _type = newType; }
        // void setHostID(char *id) { _hostID = id; }
        // void setClientID(char *id) { _clientID = id; }
        void setTimestamp(long ts) { _timestamp = ts; }
        void setPayload(Payload data) { _payload = data; }

        // Getters
        MessageType getType() const { return _type; }
        // String getHostID() const { return _hostID; }
        // String getClientID() const { return _clientID; }
        long getTimestamp() const { return _timestamp; }
        Payload getPayload() const { return _payload; }

        // Serialize the message for transmission
        String toString() const
        {
            // return messageTypeToString(_type) + "--" + _hostID + "--" + _clientID + "--" + String(_timestamp) + "--" + _payload;
            return messageTypeToString(_type) + '-' + String(_timestamp) + '-' + _payload;
        }

        // Static function to convert string bSTAT to MessageType enum
        static MessageType stringToMessageType(const String &typeStr)
        {
            if (typeStr == "DATA")
                return DATA;
            else if (typeStr == "CMD")
                return CMD;
            else if (typeStr == "STAT")
                return STAT;
            else
                return ERROR;
        }

    private:
        MessageType _type;
        char *_hostID;
        char *_clientID;
        long _timestamp;
        Payload _payload;

        // Helper to convert MessageType to String
        String messageTypeToString(MessageType _type) const
        {
            switch (_type)
            {
            case DATA:
                return "DATA";
            case CMD:
                return "CMD";
            case STAT:
                return "STAT";
            case ERROR:
                return "ERROR";
            default:
                return "UNKNOWN";
            }
        }

        // verify if _payload is valid
        bool verifyPayload(uint8_t _payload) const
        {
            if (_payload >= START_TRANSMISSION && _payload <= TEST_SIGNAL)
            {
                return true;
            }
            else if (_payload >= STARTED_TRANSMISSION && _payload <= TEST_SIGNAL_OK)
            {
                return true;
            }
            else if (_payload >= INVALID_COMMAND && _payload <= UNKNOWN_ERROR)
            {
                return true;
            }
            return false;
        }
    };
} // namespace Communication
#endif // PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
