

#ifndef SECONDMILESTONE_STATE_H
#define SECONDMILESTONE_STATE_H

#include <string>

using namespace std;

template <class T>

class State {

private:
    T state;
    double cost;
    State<T> cameFrom;

public:
    explicit State(T s) {
        this->state = s;
    }

    bool Equals(State<T> s) {
        return this->state == s;
    }
    void setCameFrom(State<T> s) {
        this->cameFrom = s;
    }

};

#endif //SECONDMILESTONE_STATE_H
