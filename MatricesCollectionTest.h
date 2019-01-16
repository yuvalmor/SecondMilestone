
#ifndef SECONDMILESTONE_MATRICESCOLLECTIONTEST_H
#define SECONDMILESTONE_MATRICESCOLLECTIONTEST_H

#include "MatricesProblem.h"
#include "BreadthFirstSearch.h"
#include "BestFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Astar.h"
#include "Solution.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

#define NUM_RUN 1
#define NUM_MATRICES 10
#define SIZE_DIFFERENCE 5
#define PROBABILITY 5
#define SECURE 5
#define START "0,0"

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

        // delete prior text files if exist
        remove("graphs.txt");
        remove("solution.txt");

    }

    // function runs the algorithms over the
    // generated designed matrices
    void run() {

        // set random operation to time measuring
        srand(time(0));

        // create file writers objects
        ofstream graphsFile("graphs.txt", ios::app);
        ofstream solutionFile("solution.txt", ios::app);
        graphsFile << NUM_MATRICES << endl;

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

                // write problem to file
                writeProblemToFile(matrix, &graphsFile);

                // run algorithms
                runAlgorithms(matrix,
                              differentMatricesCounter,
                              specificMatrixRunCounter,
                              &solutionFile);

                specificMatrixRunCounter++;
            }

            differentMatricesCounter++;

            this->height = this->height + SIZE_DIFFERENCE;
            this->width = this->width + SIZE_DIFFERENCE;
        }


        graphsFile.close();
        solutionFile.close();


    }

    /*
     * function writes the matrices to the file according
     * to a given order
     */
    void writeProblemToFile(const vector<vector<double>>& matrix,
                                ostream* graphs) {

        *graphs << this->height << "," << this->width << endl;
        *graphs << START << endl;
        *graphs << this->height-1 << "," << this->width-1 << endl;
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                if (j != this->width-1) {
                    *graphs << matrix[i][j] << ",";
                } else {
                    *graphs << matrix[i][j] << endl;
                }
            }
        }
    }

    // function initializes sizes (width and height of matrix)
    vector<vector<double>> matrixSizeInitialization(vector<vector<double>> matrix) {
        matrix.resize(this->height);
        for (int i = 0; i < this->height; i++) {
            matrix[i].resize(this->width);
        }
        return matrix;
    }

    // function initializes values using rand function
    vector<vector<double>> matrixValuesInitialization(vector<vector<double>> matrix) {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {

                // generate random between 0 and matrix size
                double num = rand()%this->height;

                // insert number for values close to end point
                if ((this->height-i < SECURE) && (this->width - j < SECURE )) {
                    matrix[i][j] = num;
                    continue;
                }
                // insert number for values close to end point
                if ((i<SECURE) && (j < SECURE )) {
                    matrix[i][j] = num;
                    continue;
                }

                // inserting walls in probability of 1:4
                int zeroChance = 1+(rand()%PROBABILITY);
                if (zeroChance == 1) {
                    matrix[i][j] = double(-1);
                } else {
                    matrix[i][j] = num;
                }

            }
        }
        return matrix;
    }

    /*
     * function writes the solution (weight and number)
     * of nodes evaluated to a file
     */
    void writeSolutionToFile(CommonSearcher<vector<int>>* s,
                            ostream* solution) {

        *solution << s->getChosenPathCost() << "," <<
                  s->getNumberOfNodesEvaluated() << endl;

    }

    /*
     * function initializes initial and goal states,
     * runs the algorithms over the given problem matrix
     * and writes solutions
     */
    void runAlgorithms(const vector<vector<double>>& matrix,
                       int differentMatricesCounter,
                       int specificMatrixRunCounter,
                       ostream* solution) {

        // start + goal initialization - two ends of matrix
        vector<int> initial;
        initial.push_back(0);
        initial.push_back(0);
        vector<int> goal;
        goal.push_back(this->height - 1);
        goal.push_back(this->width - 1);

        // creating searchable object
        Searchable<vector<int>> *m = new MatricesProblem<vector<int>>(matrix, initial, goal);

        // creating and running algorithms
        CommonSearcher<vector<int>> *s1 = new BestFirstSearch<vector<int>>();
        Solution<vector<int>> solution1 = s1->search(m);

        CommonSearcher<vector<int>> *s2 = new DepthFirstSearch<vector<int>>();
        Solution<vector<int>> solution2 = s2->search(m);

        CommonSearcher<vector<int>> *s3 = new BreadthFirstSearch<vector<int>>();
        Solution<vector<int>> solution3 = s3->search(m);

        CommonSearcher<vector<int>> *s4 = new Astar<vector<int>>();
        Solution<vector<int>> solution4 = s4->search(m);

        // write solutions to file
        writeSolutionToFile(s1, solution);
        writeSolutionToFile(s2, solution);
        writeSolutionToFile(s3, solution);
        writeSolutionToFile(s4, solution);

        // free allocations
        delete(m);
        delete(s1);
        delete(s2);
        delete(s3);
        delete(s4);

    }
};


#endif //SECONDMILESTONE_MATRICESCOLLECTIONTEST_H
