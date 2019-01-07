#ifndef SECONDMILESTONE_MYSERIALSERVER_H
#define SECONDMILESTONE_MYSERIALSERVER_H

#include <iostream>
using namespace server_side;
using namespace std;

class MySerialServer:public server_side::Server{
public:
    MySerialServer(){cout <<"good" << endl;}
};

#endif

