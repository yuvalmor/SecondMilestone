#ifndef SECONDMILESTONE_STATE_H
#define SECONDMILESTONE_STATE_H


#include <string>

using namespace std;

/*
 * a state can be any node, that has
 * a cost, a position (unique identification)
 * and a pointer to it's prior node
 */
template <class T>
class State {

private:

    // members
    T state;
    double cost;
    State<T>* cameFrom;

public:

    // check if this state equals (T wise) to s state
    bool Equals(State<T> s);

    // getters
    T getState() const {
        return this->state;
    }

    double getCost() const {
        return this->cost;
    }

    State<T>* getCameFrom() const {
        return this->cameFrom;
    }

    /*
     * recursive function from the calculation of a
     * whole path from the initial state to the current
     * state.
     */
    double getPathCost() const {
        if (nullptr == this->cameFrom) {
            return getCost();
        } else {
            return this->cameFrom->cost + getCost();
        }

    }

    // setters
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

// operator overloading for priority queue based on cost.
template <class T>
bool operator<(State<T> a, State<T> b) {
    return a.getCost() > b.getCost();
}


#endif //SECONDMILESTONE_STATE_H
