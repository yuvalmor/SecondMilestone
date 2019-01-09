#ifndef SECONDMILESTONE_MYSERIALSERVER_H
#define SECONDMILESTONE_MYSERIALSERVER_H
#include <iostream>
#include "ServerSide.h"

using namespace server_side;
using namespace std;

class MySerialServer:public Server{
public:
    void open(int port) override;
    void stop()override;
};

#endif

