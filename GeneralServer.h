/*#ifndef SECONDMILESTONE_GENERALSERVER_H
#define SECONDMILESTONE_GENERALSERVER_H

#include "ServerSide.h"
using namespace server_side;

struct serverData{
    int portNun;
    ClientHandler* clientHandler;
    bool* toListen;
public:
    serverData(int portNum,ClientHandler* clientHandler,bool* toListen){
        this->portNun=portNum;
        this->clientHandler=clientHandler;
        this->toListen=toListen;
    }
};

class GeneralServer:public Server{
    bool toListen;
    static void* openServerThread(void* param);
public:
    void open(int portNum, ClientHandler* clientHandler) override;
    void stop()override;
};

#endif
*/