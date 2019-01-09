
#ifndef SECONDMILESTONE_SEARCHER_H
#define SECONDMILESTONE_SEARCHER_H

#include "Solution.h"
#include "Searchable.h"
#include <iostream>
using namespace std;

template <class T>

class Searcher {

public:

    virtual int getNumberOfNodesEvaluated()=0;
    virtual Solution search(Searchable<T>* s)=0;

};

#endif //SECONDMILESTONE_SEARCHER_H
