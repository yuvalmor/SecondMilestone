
#ifndef SECONDMILESTONE_COMMONSEARCHER_H
#define SECONDMILESTONE_COMMONSEARCHER_H

#include <queue>
#include "Searcher.h"

using namespace std;

template <class T>
class CommonSearcher : public Searcher<T> {

private:
    int evaluatedNodes;
    //priority_queue<State<T>> openQueue;
    //priority_queue<State<T>, vector<State<T>>, CompareCost<State<T>>> openQueue;
    //set<State<T>, vector<State<T>>, CompareState<State<T>>> closedSet;

    priority_queue<State<T>> openQueue;
    queue<State<T>> closedQueue;

public:

    // ctor
    CommonSearcher() {
        this->evaluatedNodes=0;
    };

    void addStateToClosedQueue(State<T> s) {
        this->closedQueue.push(s);
    }

    bool isStateInClosedQueue(State<T> s) {
        queue<State<T>> temp = this->closedQueue;
        while (!temp.empty()) {
            if (s.Equals(temp.front())) {
                return true;
            }
            else {
                temp.pop();
            }
        }
        return false;
    }

    bool isStateInOpenQueue(State<T> s) {

        //priority_queue<State<T>, vector<State<T>>, Compare<T>> temp;
        priority_queue<State<T>> temp;
        //priority_queue<State<T>,
        //        vector<State<T>>,
          //      CompareCost<State<T>>> temp;


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
        State<T> olderState;
        olderState.setCost(double(-1));

        while (!temp.empty()) {
            olderState= temp.top();
            if (olderState.Equals(s)) {
                break;
            } else {
                temp.pop();
            }
        }

        if (olderState.getCost() == -1) {
            return false;
        }

        return olderState.getCost() > s.getCost();
    }

    void updateOpenQueue(State<T> s) {

        priority_queue<State<T>> temp;
        while (!this->openQueue.empty()) {
            State<T> top = this->openQueue.top();
            if (top.Equals(s)) {
                continue;
            } else {
                temp.push(top);
            }
            this->openQueue.pop();
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

    string getSolution() {

        string solution = "{";

        while (!this->closedQueue.empty()) {
            State<T> s = this->closedQueue.front();
            this->closedQueue.pop();

            if (!this->closedQueue.empty()) {
                State<T> n = this->closedQueue.front();
                if (n.getState()[0] > s.getState()[0] ) {
                    solution += "Down, ";
                    continue;
                }
                if (n.getState()[0] < s.getState()[0] ) {
                    solution += "Up, ";
                    continue;
                }
                if (n.getState()[0] == s.getState()[0] ) {
                    if (n.getState()[1] > s.getState()[1]) {
                        solution += "Right, ";
                        continue;
                    }
                    solution += "Left, ";
                }
            }
        }

        solution = solution.substr(0, solution.size()-2);
        solution+= "}";

        return solution;
    }


    virtual Solution<T> search(Searchable<T>* s)=0;

};

#endif //SECONDMILESTONE_COMMONSEARCHER_H
