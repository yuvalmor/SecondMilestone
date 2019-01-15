
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

        // delete prior files from memory
        remove("graphs.txt");
        remove("solution.txt");

    }


    // function operation - runs the algorithms over the
    // generated designed matrices
    void run() {

        // set random operation to time measuring
        srand(time(0));

        // file writers
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

            this->height = this->height + 5;
            this->width = this->width + 5;
        }


        graphsFile.close();
        solutionFile.close();


    }

    void writeProblemToFile(const vector<vector<double>>& matrix,
                                ostream* graphs) {

        *graphs << this->height << "," << this->width << endl;
        *graphs << "0,0" << endl;
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

                if (abs(i-j) <= 1) {
                    matrix[i][j] = double(1);
                    continue;
                }

                // generate random between 0 and matrix size
                double num = rand()%this->height;

                // inserting walls
                int zeroChance = 1+(rand()%5);
                if (zeroChance == 1) {
                    matrix[i][j] = double(-1);
                } else {
                    matrix[i][j] = num;
                }

            }
        }
        return matrix;
    }

    void writeSolutionToFile(CommonSearcher<vector<int>>* s,
                            ostream* solution) {

        *solution << s->getChosenPathCost() << "," <<
          s->getNumberOfNodesEvaluated() << endl;

    }

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
        Solution<vector<int>> solution2 = s1->search(m);

        CommonSearcher<vector<int>> *s2 = new DepthFirstSearch<vector<int>>();
        Solution<vector<int>> solution4 = s2->search(m);

        CommonSearcher<vector<int>> *s3 = new BreadthFirstSearch<vector<int>>();
        Solution<vector<int>> solution3 = s3->search(m);

        CommonSearcher<vector<int>> *s4 = new Aster<vector<int>>();
        Solution<vector<int>> solution1 = s4->search(m);

        // write solutions to file
        writeSolutionToFile(s1, solution);
        writeSolutionToFile(s2, solution);
        writeSolutionToFile(s3, solution);
        writeSolutionToFile(s4, solution);

        cout << "Astar solution : " << solution4.getSolution() << endl;

        for (int i=0; i<this->height; i++) {
            for (int j=0; j<this->width; j++) {
                cout << matrix[i][j] << ",";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;

    }
};


#endif //SECONDMILESTONE_MATRICESCOLLECTIONTEST_H
