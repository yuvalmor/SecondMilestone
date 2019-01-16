
#ifndef SECONDMILESTONE_SEARCHER_H
#define SECONDMILESTONE_SEARCHER_H
#include "Searchable.h"
#include <iostream>

using namespace std;

template <class T>
class Solution;
template <class T>
class Searcher {

public:

    // return the number of evaluated nodes
    virtual int getNumberOfNodesEvaluated()=0;

    // search a path from initial to goal.
    virtual Solution<T> search(Searchable<T>* s)=0;

};


#endif
