#include "SmartServer.h"


SmartServer::SmartServer(/* args */)
{
    uuid.generate();
    Log.noticeln(F("Server UUID generated: %s\n"), uuid.toCharArray());
}

SmartServer::~SmartServer()
{
}

void SmartServer::getUUIDAsCharArray(char* output) {
    sprintf(output, "%s", uuid.toCharArray());
    Log.traceln(F("Retrieving Server UUID: %s\n"), output);
}