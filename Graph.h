#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

class Graph{

    private:
        int** edges;/// Matrix containing all the edges and their weights
        int* vertices; /// Array containing vertices weights
        int** groupsBounds; /// Matrix groupsNumber x 2 which position 0 is lower Bound and position 1 is upper Bound
        int verticesNumber; /// Total number of vertices
        int groupsNumber; /// Total number of groups

        void readFile(char fileName []);
        void insertEdge(int vertexOne, int vertexTwo, int edgeWeight);

    public:
        Graph(char fileName []);
        ~Graph();
        void printGraph();
        void printGraphList();
        void printVertexWeight();
        void printGroupsBounds();

};


#endif // GRAPH_H_INCLUDED
