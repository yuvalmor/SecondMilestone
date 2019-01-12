
#ifndef SECONDMILESTONE_BESTFIRSTSEARCH_H
#define SECONDMILESTONE_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"

#include <set>

template <class T>
class BestFirstSearch: public CommonSearcher<T> {

public:

    // ctor
    BestFirstSearch<T>():CommonSearcher<T>(){}

    Solution<T> search(Searchable<T>* s) override {

        // initialize member 'openQueue' (priority Queue) with A
        CommonSearcher<T>::addToOpenQueue(s->getInitialState());

        // loop over openQueue states
        while (CommonSearcher<T>::openQueueSize() > 0) {

            // get the best state from the queue to 'n' (and remove from open)
            State<T> n = CommonSearcher<T>::popOpenQueue();

            // add the n state to the set
            //CommonSearcher<T>::addStateToSet(n);
            CommonSearcher<T>::addStateToClosedQueue(n);

            // check if the current state is the goal.
            // if yes return path (or path cost)
            if (n.Equals(s->isStateGoal(n))) {
                Solution<T> sol;
                sol.setSolution(CommonSearcher<T>::getSolution());
                return sol;
            }

            // get the neighbors of 'n'
            set<State<T>> neighbors = s->getAllPossibleStates(n);

            // loop over 'n'/s neighbors
            for (auto cState : neighbors) {

                // check if 'currentState' is in openQueue or closedSet
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenQueue(cState);
                //bool isStateInClosed = CommonSearcher<T>::isStateInClosedSet(cState);
                bool isStateInClosed = CommonSearcher<T>::isStateInClosedQueue(cState);

                if (!isStateInClosed && !isStateInOpen) {

                    // update that you came to currentState from 'n'
                    // and update the cost, then add currentState to
                    // to the openQueue

                    cState.setCameFrom(&n);
                    cState.setCost(cState.getCost());

                    CommonSearcher<T>::addToOpenQueue(cState);

                    // move on to next neighbor
                    continue;
                }

                if (CommonSearcher<T>::isNewPathShorter(cState)) {
                    CommonSearcher<T>::updateOpenQueue(cState);
                }

            }
        }
    }
};

#endif //SECONDMILESTONE_BESTFIRSTSEARCH_H
