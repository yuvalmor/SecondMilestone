#ifndef SECONDMILESTONE_CLIENTHANDLER_H
#define SECONDMILESTONE_CLIENTHANDLER_H

/**
 * The interface ClientHandler, set the call classification,
 * And the way to handle the call.
 */
class ClientHandler{
public:
    // Handle the client in the given socket
    virtual void handleClient(int socket) = 0;
};

#endif