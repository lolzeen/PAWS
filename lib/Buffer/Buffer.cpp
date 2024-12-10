#include "Buffer.h"
#include "SensorData.h"
#include "ArduinoLog.h"
#include "Config.h"

template<typename Type>
void Buffer<Type>::advanceBufferHead() {
    Log.traceln(F("Advancing buffer head from position %d...\n"), bufferHead);
    bufferHead = (bufferHead + 1) % BUFFER_SIZE;
    if (bufferHead == bufferTail && bufferHead == BUFFER_SIZE)
    {
        Log.warningln(F("Buffer is full. Buffer head at %d\n"), bufferHead);
        bufferIsFull = true;
    }
    else
    {
        Log.noticeln(F("Buffer head advanced to %d. Buffer is not full.\n"), bufferHead);
        bufferIsFull = false;
    }
}
template<typename Type>
void Buffer<Type>::advanceBufferTail() {
    Log.traceln(F("Advancing buffer tail from position %d...\n"), bufferTail);
    bufferTail = (bufferTail + 1) % BUFFER_SIZE;
    Log.noticeln(F("Buffer tail advanced to %d\n"), bufferTail);
}
template<typename Type>
void Buffer<Type>::includeData(Type data) {
    Log.traceln(F("Saving data at buffer position %d\n"), bufferHead);
    circularBuffer[bufferHead] = data;
    advanceBufferHead();
}

template<typename Type>
Type Buffer<Type>::retieveData() {
    uint8_t tempIndex = bufferTail;
    advanceBufferTail();
    return circularBuffer[tempIndex];
}