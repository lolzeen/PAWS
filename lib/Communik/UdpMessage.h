#ifndef PAWS_COMMUNIK_UDPMESSAGE_H
#define PAWS_COMMUNIK_UDPMESSAGE_H
#include<Arduino.h>

class UdpMessage {
public:
    // Enum for message types
    enum MessageType { DATA, CMD, STAT, ERROR };

    // Constructor
    UdpMessage(MessageType type,const String& hostID, const String& clientID,  const String& payload)
        : type(type), hostID(hostID), clientID(clientID), payload(payload) {
        timestamp = millis(); // Timestamp in milliseconds since program start
    }

    // Setters
    void setType(MessageType newType) { type = newType; }
    void setHostID(const String& id) {hostID = id; }
    void setClientID(const String& id) { clientID = id; }
    void setTimestamp(long ts) { timestamp = ts; }
    void setPayload(const String& data) { payload = data; }

    // Getters
    MessageType getType() const { return type; }
    String getHostID() const {return hostID; }
    String getClientID() const { return clientID; }
    long getTimestamp() const { return timestamp; }
    String getPayload() const { return payload; }

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
};

#endif // PAWS_COMMUNIK_UDPMESSAGE_H
