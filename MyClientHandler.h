#ifndef SECONDMILESTONE_MYCLIENTHANDLER_H
#define SECONDMILESTONE_MYCLIENTHANDLER_H

#include "ClientHandler.h"

class MyClientHandler:public ClientHandler{
public:
    void handleClient(int socket);
};

#endif
