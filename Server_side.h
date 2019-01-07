#ifndef SECONDMILESTONE_SERVER_SIDE_H
#define SECONDMILESTONE_SERVER_SIDE_H

namespace server_side{
    class Server{
    public:
        virtual void open(int port)=0;
        virtual void stop() =0;
    };
}

#endif //SECONDMILESTONE_SERVER_SIDE_H
