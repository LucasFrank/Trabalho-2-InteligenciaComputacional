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
        float** edges;/// 2d-Array containing all the edges and their weights
        float* vertices; /// Array containing vertices weights
        float** groupsBounds; /// 2d-Array groupsNumber x 2 which position 0 is lower Bound and position 1 is upper Bound
        int verticesNumber; /// Total number of vertices
        int groupsNumber; /// Total number of groups

        void readFile(char fileName [], char readType);
        void insertEdge(int vertexOne, int vertexTwo, float edgeWeight);

    public:
        Graph(char fileName [], char readType);
        ~Graph();
        void printGraph();
        void printGraphList();
        void printVertexWeight();
        void printGroupsBounds();

};


#endif // GRAPH_H_INCLUDED
