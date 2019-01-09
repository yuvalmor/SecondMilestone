
#ifndef SECONDMILESTONE_COMMONSEARCHER_H
#define SECONDMILESTONE_COMMONSEARCHER_H

using namespace std;

#include "State.h"
#include "PriorityQueue.h"
#include "Searcher.h"

template <class T>

class CommonSearcher : public Searcher<T> {

private:
    int evaluatedNodes;
    PriorityQueue<State<T>> openList;

public:

    // ctor
    CommonSearcher() {
        this->evaluatedNodes=0;
    };

    // new functions

    bool isStateInOpenList(State<T> s) {

        // create iterator over the queue
        return true;
    }

    void addToOpenList(State<T> s) {
        this->openList.getPriorityQueue().push(s);
    }

    State<T> popOpenList() {
        this->evaluatedNodes++;
        State<T> s = this->openList.getPriorityQueue().top();
        this->openList.getPriorityQueue().pop();
        return s;
    }

    int OpenListSize() {
        return (int)this->openList.getPriorityQueue().size();
    };


    // Searcher functions

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }


    virtual Solution search(Searchable<T>* s)=0;

};

#endif //SECONDMILESTONE_COMMONSEARCHER_H
