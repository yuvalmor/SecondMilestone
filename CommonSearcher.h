
#ifndef SECONDMILESTONE_COMMONSEARCHER_H
#define SECONDMILESTONE_COMMONSEARCHER_H

#include <queue>
#include <stack>
#include "Searcher.h"

using namespace std;

template <class T>
class CommonSearcher : public Searcher<T> {

private:

    int evaluatedNodes;
    priority_queue<State<T>> openQueue;

public:

    // ctor
    CommonSearcher() {
        this->evaluatedNodes=0;
    };

    bool isStateInOpenQueue(State<T> s) {

        priority_queue<State<T>> temp;

        temp = openQueue;

        while (!temp.empty()) {
            if (s.Equals(temp.top())) {
                return true;
            } else{
                temp.pop();
            }
        }
        return false;
    }

    void addToOpenQueue(State<T> s) {
        this->openQueue.push(s);
    }

    bool isNewPathShorter(State<T> s) {

        priority_queue<State<T>> temp = this->openQueue;

        while (!temp.empty()) {
            State<T>* olderState = new State<T>(temp.top());
            if (olderState->Equals(s)) {
                return olderState->getCost() > s.getCost();
            } else {
                temp.pop();
            }
        }

        return false;
    }

    void updateOpenQueue(State<T> s) {

        priority_queue<State<T>> temp;
        while (!this->openQueue.empty()) {
            State<T> top = this->openQueue.top();
            if (top.Equals(s)) {
                this->openQueue.pop();
            } else {
                temp.push(top);
                this->openQueue.pop();
            }
        }
        temp.push(s);
        this->openQueue = temp;
    }

    State<T> popOpenQueue() {

        // increase the path visited nodes
        this->evaluatedNodes++;

        // get that top priority state from the queue
        State<T> s = this->openQueue.top();

        // remove the best state from the queue
        this->openQueue.pop();

        return s;
    }

    int openQueueSize() {
        return (int)this->openQueue.size();
    };

    // Searcher functions

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    virtual Solution<T> search(Searchable<T>* s)=0;

};

#endif //SECONDMILESTONE_COMMONSEARCHER_H
