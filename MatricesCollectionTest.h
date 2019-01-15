
#ifndef SECONDMILESTONE_MATRICESCOLLECTIONTEST_H
#define SECONDMILESTONE_MATRICESCOLLECTIONTEST_H

#include "MatricesProblem.h"
#include "BreadthFirstSearch.h"
#include "BestFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Astar.h"
#include "Solution.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define NUM_RUN 1
#define NUM_MATRICES 10

// checking algorithms complexity
class MatricesCollectionTest {

private:

    // matrix size values
    int height;
    int width;

    // num of different matrices
    int numMatrices;

    // num of run times per matrix
    int runNumber;


public:

    // ctor
    MatricesCollectionTest(int height, int width) {

        this->height = height;
        this->width = width;
        this->numMatrices = NUM_MATRICES;
        this->runNumber = NUM_RUN;

    }

    // function operation - runs the algorithms over the
    // generated designed matrices
    void run() {

        // set random operation to time measuring
        srand(time(0));

        // running the algorithms over X matrices
        int differentMatricesCounter=1;
        while (differentMatricesCounter <= this->numMatrices) {

            // running over each matrix Y times
            int specificMatrixRunCounter=1;
            while (specificMatrixRunCounter <= this->runNumber) {

                vector<vector<double>> matrix;

                // matrix initialization
                matrix = matrixSizeInitialization(matrix);

                // values initialization
                matrix = matrixValuesInitialization(matrix);

                // run algorithms
                runAlgorithms(matrix,
                              differentMatricesCounter,
                              specificMatrixRunCounter);

                specificMatrixRunCounter++;
            }

            differentMatricesCounter++;

            this->height = this->height + 5;
            this->width = this->width + 5;
        }

    }

    // size initialization
    vector<vector<double>> matrixSizeInitialization(vector<vector<double>> matrix) {
        matrix.resize(this->height);
        for (int i = 0; i < this->height; i++) {
            matrix[i].resize(this->width);
        }
        return matrix;
    }

    // values initialization using rand function
    vector<vector<double>> matrixValuesInitialization(vector<vector<double>> matrix) {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {

                // generate random between 0 and matrix size
                double num = rand()%this->height;

                // inserting walls
                int zeroChance = 1+(rand()%10);
                if (zeroChance == 1 ) {
                    matrix[i][j] = double(-1);
                } else {
                    matrix[i][j] = num;
                }
            }
        }
        return matrix;
    }

    void runAlgorithms(vector<vector<double>> matrix,
                       int differentMatricesCounter,
                       int specificMatrixRunCounter) {

        // start + goal initialization - two ends of matrix
        vector<int> initial;
        initial.push_back(1);
        initial.push_back(1);
        vector<int> goal;
        goal.push_back(this->height - 1);
        goal.push_back(this->width - 1);

        // creating searchable object
        Searchable<vector<int>> *m = new MatricesProblem<vector<int>>(matrix, initial, goal);

        // creating and running algorithms
        CommonSearcher<vector<int>> *s1 = new Aster<vector<int>>();
        Solution<vector<int>> solution1 = s1->search(m);

        CommonSearcher<vector<int>> *s2 = new BestFirstSearch<vector<int>>();
        Solution<vector<int>> solution2 = s2->search(m);

        CommonSearcher<vector<int>> *s3 = new BreadthFirstSearch<vector<int>>();
        Solution<vector<int>> solution3 = s3->search(m);

        CommonSearcher<vector<int>> *s4 = new DepthFirstSearch<vector<int>>();
        Solution<vector<int>> solution4 = s4->search(m);

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "Astar path cost: " <<
             s1->getChosenPathCost() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "BestFirstSearch path cost: " <<
             s2->getChosenPathCost() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "BreadthFirstSearch path cost: " <<
             s3->getChosenPathCost() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "DepthFirstSearch path cost: " <<
             s4->getChosenPathCost() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "Astar nodes evaluated: " <<
             s1->getNumberOfNodesEvaluated() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "BestFirstSearch nodes evaluated: " <<
             s2->getNumberOfNodesEvaluated() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "BreadthFirstSearch nodes evaluated: " <<
             s3->getNumberOfNodesEvaluated() << endl;

        cout << "matrix number " <<
             differentMatricesCounter << ", run number " <<
             specificMatrixRunCounter << ", " <<
             "DepthFirstSearch nodes evaluated: " <<
             s4->getNumberOfNodesEvaluated() << endl;
    }

};


#endif //SECONDMILESTONE_MATRICESCOLLECTIONTEST_H
