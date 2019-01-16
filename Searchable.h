#ifndef SECONDMILESTONE_SEARCHABLE_H
#define SECONDMILESTONE_SEARCHABLE_H

#include <set>
#include <vector>
#include "State.h"

using namespace std;

template <class T>
class Searchable {

protected:

    // members
    vector<vector<State<T>>> matrix;
    State<T> initial;
    State<T> goal;

public:

    // return initial state.
    virtual State<T> getInitialState()=0;

    // return goal state
    virtual State<T> isStateGoal(State<T> s)=0;

    // return the set of states that are reachable from s state
    virtual multiset<State<T>> getAllPossibleStates(State<T> s)=0;

    // return problem structure
    vector<vector<State<T>>> returnStructure() const {
        return this->matrix;
    }

    // need to implement something in hash set
};
#endif
