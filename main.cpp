#include <iostream>
#include "MySerialServer.h"
#include "ServerSide.h"
using namespace server_side;

int main() {
   Server* server = new MySerialServer();
   return 0;
}