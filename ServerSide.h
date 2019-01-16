#ifndef SECONDMILESTONE_SERVERSIDE_H
#define SECONDMILESTONE_SERVERSIDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ClientHandler.h"

/**
 * namespace - server side
 */
namespace server_side{
    class Server{
    public:
        // open the server
        virtual void open(int portNum,ClientHandler* clientHandler)=0;
        // close the server
        virtual void stop()=0;
    };
}

#endif