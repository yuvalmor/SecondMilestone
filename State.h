

#ifndef SECONDMILESTONE_STATE_H
#define SECONDMILESTONE_STATE_H

#include <string>

using namespace std;

template <class T>
class State {

private:
    T state;
    double cost;
    State<T>* cameFrom;

public:

    bool Equals(State<T> s);

    T getState() const {
        return this->state;
    }

    double getCost() const {
        if (nullptr == this->cameFrom) {
            return this->cost;
        } else {
            return this->cameFrom->getCost() +this->cost;
        }
    }

    void setState(T s){
        this->state = s;
    }
    void setCost(double cost) {
        this->cost = cost;
    }
    void setCameFrom(State<T>* s) {
        this->cameFrom = s;
    }

};

template <class T>
bool State<T>::Equals(State<T> s) {
    return (this->state == s.state) ;
}

template <class T>
bool operator<(State<T> a, State<T> b) {
    return a.getCost() > b.getCost();
}

#endif //SECONDMILESTONE_STATE_H
