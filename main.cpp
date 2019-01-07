#include <iostream>
#include "MySerialServer.h"

namespace server_side{
    class Server{
    public:
        virtual void open(int port)=0;
        virtual void stop()=0;
    };
}

int main() {
   return 0;
}