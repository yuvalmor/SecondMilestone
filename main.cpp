#include <iostream>
#include "MySerialServer.h"
using namespace server_side;

int main() {
    Server* server = new MySerialServer();
    return 0;
}