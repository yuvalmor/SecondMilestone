
#ifndef SECONDMILESTONE_SEARCHABLE_H
#define SECONDMILESTONE_SEARCHABLE_H

#include <set>
#include "State.h"

using namespace std;

template <class T>
class Searchable {
public:
    virtual State<T> getInitialState()=0;
    virtual State<T> isStateGoal(State<T> s)=0;

    // return the set of states that are reachable from s state
    virtual set<State<T>> getAllPossibleStates(State<T> s)=0;

    // need to implement something in hash set
};

#endif //SECONDMILESTONE_SEARCHABLE_H
