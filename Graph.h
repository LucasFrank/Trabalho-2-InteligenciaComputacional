#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

class Graph{

    private:
        float** edges;/// 2d-Array containing all the edges and their weights
        float* vertices; /// Array containing vertices weights
        float** groupsBounds; /// 2d-Array groupsNumber x 2 which position 0 is lower Bound and position 1 is upper Bound
        int verticesNumber; /// Total number of vertices
        int groupsNumber; /// Total number of groups

        void readFile(char fileName [], char readType);
        void insertEdge(int vertexOne, int vertexTwo, float edgeWeight);

        float calculateTotalEdgeWeight(vector< vector<int> > sol);
        void setVertexCoverWithNoEdges(int* verticesCover);
        bool forcedStopCondition(int* groupsAux);
        bool isCover(int* verticesAux);
        bool verifyBounds(vector< vector<int> > sol);
        bool verifyEdges(int vertex);
        int getVertex(int* vert); /// Return the first element not used in vert
        int getVertexNeighbor(int* vert, int vertexValue); /// Return the first element not used in vert that is neighbor with vertexValue
        int getVertexByWeight(int* vert); /// Return the element with the biggest weight
        int getVertexByWeightNeighbor(int* vert,vector<int> group);/// Return the element with the biggest weight in the neighbor of the group elements
        int getVertexByWeightNeighbor(int* vert,vector<int> group,vector<int> fail);
        int getVertexEdgeWeight(int vertex);
        vector<int> getNeighborhood(vector<int> group);
        vector< vector<int> > greedyHeuristic();
        vector< vector<int> > randomizeSolution(vector< vector<int> > sol);
        void printSolution(vector< vector<int> > sol);

        vector< vector<int> > localSearch(bool firstBest, bool randomGreedy, int timeLimit);
        vector< vector<int> > localSearchRandom(bool randomGreedy, int timeLimit);
        float calculateVertexGroupWeight(vector<int> group);


        void writeFile(ofstream *out, bool firstBest, bool random, bool randomGreedy, float bestWeight, float mean, vector< vector<int> > sol);

    public:
        Graph(char fileName [], char readType);
        ~Graph();
        void printGraph();
        void printGraphList();
        void printVertexWeight();
        void printGroupsBounds();
        void runGreedyAlgorithm();
        void runLocalSearchAlgorithm(bool firstBest, bool random, bool randomGreedy, int timeLimit, ofstream *out);
        void calculateTotalEdgeWeightVerification();

};


#endif // GRAPH_H_INCLUDED
