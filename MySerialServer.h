#ifndef SECONDMILESTONE_MYSERIALSERVER_H
#define SECONDMILESTONE_MYSERIALSERVER_H

#include <iostream>
#include "ServerSide.h"
#include "ClientHandler.h"

using namespace server_side;
using namespace std;

class MySerialServer:public Server{
    bool toListen;
public:
    void open(int port, ClientHandler* clientHandler) override;
    void stop()override;
};

#endif

