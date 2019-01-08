#ifndef SECONDMILESTONE_SERVERSIDE_H
#define SECONDMILESTONE_SERVERSIDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace server_side{
    class Server{
    public:
        virtual void open(int port)=0;
        virtual void stop()=0;
    };
}

#endif
