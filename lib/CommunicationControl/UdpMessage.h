#ifndef PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
#define PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
#include<Arduino.h>

namespace Communication {
class UdpMessage {
public:
    // Enum for message types
    enum MessageType { DATA, CMD, STAT, ERROR };
    enum CommandPayloads : uint8_t {
    START_TRANSMISSION = 0,      // Signal to start data transmission
    STOP_TRANSMISSION = 1,       // Signal to stop data transmission
    SENSOR_DATA = 2,             // Generic sensor data payload
    HEARTBEAT = 3,               // Keep-alive signal between devices
    CONFIG_UPDATE = 4,           // Configuration update from server to client
    ACKNOWLEDGMENT = 5,          // Acknowledgment of received data
    ERROR_MESSAGE = 6,           // Error report from client or server
    REQUEST_STATUS = 7,          // Request status of a client
    STATUS_RESPONSE = 8,         // Response with status information
    CONNECTION_LOST = 9,         // Notification of a lost connection
    DATA_END = 10,                // Signal that all data has been sent
    CALIBRATION_DATA = 11,        // Data for calibrating sensors
    RESET_DEVICE = 12,            // Signal to reset a client or server
    TEST_SIGNAL = 13              // Signal for testing communication
    };
    enum StatusPayloads {
    STARTED_TRANSMISSION = 20,    // Indicates transmission has started
    STOPPED_TRANSMISSION = 21,    // Indicates transmission has stopped
    SENSOR_DATA_RECEIVED = 22,    // Acknowledges receipt of sensor data
    HEARTBEAT_RECEIVED = 23,      // Acknowledges heartbeat signal
    CONFIG_UPDATED = 24,          // Confirms successful configuration update
    ACK_RECEIVED = 25,            // Acknowledges a received acknowledgment
    ERROR_DETECTED = 26,          // Indicates an error was detected
    STATUS_OK = 27,               // General status indicating "all is well"
    CONNECTION_ESTABLISHED = 28,  // Confirms a successful connection
    CONNECTION_LOST = 29,         // Indicates the connection was lost
    DATA_TRANSMISSION_DONE = 30,  // Confirms that data transmission is complete
    SENSOR_CALIBRATED = 31,       // Indicates successful sensor calibration
    DEVICE_RESET_DONE = 32,       // Confirms device reset was successful
    TEST_SIGNAL_OK = 33          // Confirms the test signal was received successfully
    };
    enum ErrorPayloads {
    INVALID_COMMAND = 40,        // Received an unrecognized or unsupported command
    TRANSMISSION_FAILED = 41,    // Failed to send or receive data
    SENSOR_ERROR = 42,           // Problem with sensor operation or data
    CONFIG_ERROR = 43,           // Failed to apply configuration settings
    CONNECTION_TIMEOUT = 44,     // Lost connection due to a timeout
    ACK_TIMEOUT = 45,            // Did not receive acknowledgment in time
    MEMORY_ALLOCATION_FAIL = 46, // Failed to allocate memory
    UNSUPPORTED_PAYLOAD = 47,    // Payload type not recognized or supported
    PERMISSION_DENIED = 48,      // Command or action not permitted
    DEVICE_BUSY = 49,            // Device is currently busy with another operation
    RESET_FAILED = 50,           // Failed to reset the device
    CALIBRATION_FAILED = 51,     // Sensor calibration failed
    DATA_OVERFLOW = 52,          // Received data exceeds buffer capacity
    DATA_CORRUPTED = 53,         // Received data is corrupted
    UNKNOWN_ERROR = 54          // Catch-all for unexpected errors
    };

    // Constructor
    UdpMessage(MessageType type,const char& hostID, const char& clientID,  const char& payload)
        : type(type), hostID(hostID), clientID(clientID), payload(payload) {
        timestamp = millis(); // Timestamp in milliseconds since program start
    }
    UdpMessage(MessageType type,const String& hostID, const String& clientID,  const char& payload)
        : type(type), hostID(hostID), clientID(clientID), payload(payload) {
        timestamp = millis(); // Timestamp in milliseconds since program start
    }

    // Setters
    void setType(MessageType newType) { type = newType; }
    void setHostID(const String& id) {hostID = id; }
    void setClientID(const String& id) { clientID = id; }
    void setTimestamp(long ts) { timestamp = ts; }
    void setPayload(const uint8_t& data) { payload = data; }

    // Getters
    MessageType getType() const { return type; }
    String getHostID() const {return hostID; }
    String getClientID() const { return clientID; }
    long getTimestamp() const { return timestamp; }
    uint8_t getPayload() const { return payload; }

    // Serialize the message for transmission
    String toString() const {
        return messageTypeToString(type) + "--" + hostID + "--" + clientID + "--" + String(timestamp) + "--" + payload;
    }

    // Static function to convert string bSTAT to MessageType enum
    static MessageType stringToMessageType(const String& typeStr) {
        if (typeStr == "DATA") return DATA;
        else if (typeStr == "CMD") return CMD;
        else if (typeStr == "STAT") return STAT;
        else return ERROR;
    }

private:
    MessageType type;
    String hostID;
    String clientID;
    long timestamp;
    String payload;

    // Helper to convert MessageType to String
    String messageTypeToString(MessageType type) const {
        switch (type) {
            case DATA: return "DATA";
            case CMD: return "CMD";
            case STAT: return "STAT";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

    // verify if payload is valid
    bool verifyPayload(uint8_t payload) const {
        if (payload >= START_TRANSMISSION && payload <= TEST_SIGNAL) {return true;}
        else if (payload >= STARTED_TRANSMISSION && payload <= TEST_SIGNAL_OK) {return true;}
        else if (payload >= INVALID_COMMAND && payload <= UNKNOWN_ERROR) {return true;}
        return false;
    }
};
} // namespace Communication
#endif // PAWS_COMMUNICATION_CONTROL_UDPMESSAGE_H
