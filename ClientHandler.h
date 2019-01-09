#ifndef SECONDMILESTONE_CLIENTHANDLER_H
#define SECONDMILESTONE_CLIENTHANDLER_H

/**
 * The interface ClientHandler represent the specific way of communication with the client
 */
class ClientHandler{
public:
    virtual void handleClient(int socket) = 0;
};

#endif //SECONDMILESTONE_CLIENTHANDLER_H
