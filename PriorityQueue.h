

#ifndef SECONDMILESTONE_PRIORITYQUEUE_H
#define SECONDMILESTONE_PRIORITYQUEUE_H

#include <queue>
#include "State.h"

using namespace std;

template <class MyPriority> class P;
template <class T>

class PriorityQueue {
private:
    priority_queue<State<T>> myQueue;

public:

    PriorityQueue()= default;

    priority_queue<State<T>> getPriorityQueue() const {
        return this->myQueue;
    }

};

#endif //SECONDMILESTONE_PRIORITYQUEUE_H
