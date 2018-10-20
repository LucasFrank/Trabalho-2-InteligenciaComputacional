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

        vector< vector<int> > localSearch(bool firstBest, int timeLimit);
        vector< vector<int> > localSearchRandom(int timeLimit);
        float calculateVertexGroupWeight(vector<int> group);

    public:
        Graph(char fileName [], char readType);
        ~Graph();
        void printGraph();
        void printGraphList();
        void printVertexWeight();
        void printGroupsBounds();
        void runGreedyAlgorithm();
        void runLocalSearchAlgorithm(bool firstBest, bool random, int timeLimit);

};


#endif // GRAPH_H_INCLUDED
