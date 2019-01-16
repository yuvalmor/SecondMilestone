
#ifndef SECONDMILESTONE_BESTFIRSTSEARCH_H
#define SECONDMILESTONE_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"
#include <set>

template <class T>
class BestFirstSearch: public CommonSearcher<T> {

private:

    // queue for processed nodes.
    queue<State<T>> closedQueue;

public:

    // ctor
    BestFirstSearch<T>():CommonSearcher<T>(){}

    // searching for the cheapest path from initial to goal node
    Solution<T> search(Searchable<T>* s) override {

        // adding the initial node to the open queue
        CommonSearcher<T>::addToOpenQueue(s->getInitialState());

        // initialize solution
        Solution<T> sol;

        // loop over openQueue states
        while (CommonSearcher<T>::openQueueSize() > 0) {

            // get the best state from the queue to 'n' (and remove from open)
            State<T>* n = new State<T>(CommonSearcher<T>::popOpenQueue());

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
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenQueue(neighbor);
                bool isStateInClosed = CommonSearcher<T>::isStateInClosedQueue(neighbor, this->closedQueue);

                // treat new neighbor we have not yet met
                if (!isStateInClosed && !isStateInOpen) {

                    // set that we have come ti neighbor from n
                    neighbor.setCameFrom(n);

                    // set the path cost to neighbor throw n
                    neighbor.setCost(neighbor.getPathCost());

                    // add neighbor to the open queue
                    CommonSearcher<T>::addToOpenQueue(neighbor);

                    continue;
                }

                neighbor.setCameFrom(n);
                neighbor.setCost(neighbor.getPathCost());

                // check if this new path to neighbor throw n is better than
                // path we already have
                if (CommonSearcher<T>::isNewPathShorterThanOpen(neighbor) ||
                    CommonSearcher<T>::isNewPathShorterThanClosed(neighbor, this->closedQueue)) {

                    // if neighbor is not in open list we add it
                    if (!isStateInOpen) {
                        CommonSearcher<T>::addToOpenQueue(neighbor);
                    } else {
                        // if neighbor is in open list we update it's priority
                        CommonSearcher<T>::updateOpenQueue(neighbor);
                    }

                }

            }
        }
        return sol;
    }


};

#endif
