#ifndef PAWS_LIB_BUFFER_H
#define PAWS_LIB_BUFFER_H
#include <Arduino.h>

template <typename Type>
class Buffer
{

public:
    Buffer() {};
    ~Buffer() {};

    uint8_t getBufferHead() const { return bufferHead; }
    uint8_t getBufferTail() const { return bufferTail; }
    uint8_t getBufferSize() const { return BUFFER_SIZE; }
    Type *getBuffer() { return circularBuffer; }
    bool isBufferFull() const { return bufferIsFull; }
    void includeData(Type data);
    Type retieveData();

private:
    static const uint8_t BUFFER_SIZE = 40;
    Type circularBuffer[BUFFER_SIZE];
    uint8_t bufferHead = 0;
    uint8_t bufferTail = 0;
    bool bufferIsFull = false;

    void advanceBufferHead();
    void advanceBufferTail();
};

#endif // PAWS_LIB_BUFFER_H