
#ifndef SECONDMILESTONE_BREADTHFIRSTSEARCH_H
#define SECONDMILESTONE_BREADTHFIRSTSEARCH_H

#include "CommonSearcher.h"
#include <set>

template <class T>
class BreadthFirstSearch: public CommonSearcher<T> {

private:
    queue<State<T>> closedQueue;

public:

    // ctor
    BreadthFirstSearch<T>():CommonSearcher<T>(){}

    // searching for some path from initial to goal node
    Solution<T> search(Searchable<T>* s) override {

        // adding the initial node to the open queue
        CommonSearcher<T>::addToOpenRegularQueue(s->getInitialState());

        // initialize solution
        Solution<T> sol;

        // loop over openQueue states
        while (CommonSearcher<T>::openQueueRegularSize() > 0) {

            // get the best state from the queue to 'n' (and remove from open)
            State<T>* n = new State<T>(CommonSearcher<T>::popOpenRegularQueue());

            // push current best node to closed queue
            this->closedQueue.push(*n);

            // check if we have come to goal node and return solution
            if (n->Equals(s->isStateGoal(*n))) {
                CommonSearcher<T>::setChosenPathWeight(n->getCost());
                sol.setSolution(CommonSearcher<T>::getSolution(s, this->closedQueue));
                return sol;
            }

            // get the neighbors of 'n'
            multiset<State<T>> neighbors = s->getAllPossibleStates(*n);

            // loop over 'n'/s neighbors
            for (auto neighbor : neighbors) {

                // check if 'neighbor' is in openQueue or closedSet
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenRegularQueue(neighbor);
                bool isStateInClosed = CommonSearcher<T>::isStateInClosedQueue(neighbor, this->closedQueue);

                // if neighbor in closed queue - do nothing
                if (isStateInClosed) {
                    continue;
                }

                // if neighbor is not in open queue(new neighbor)
                if (!isStateInOpen) {

                    // set that we have come to neighbor from n
                    neighbor.setCameFrom(n);
                    // set the cost (not needed for path finding)
                    neighbor.setCost(neighbor.getPathCost());

                    // add neighbor to the open queue
                    CommonSearcher<T>::addToOpenRegularQueue(neighbor);
                }

            }
        }
        return sol;
    }


};



#endif //SECONDMILESTONE_BREADTHFIRSTSEARCH_H
