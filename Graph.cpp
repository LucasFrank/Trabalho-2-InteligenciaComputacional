#include "Graph.h"


Graph::Graph(char fileName []){

    readFile(fileName);
}

Graph::~Graph(){

    for(int i = 0; i < verticesNumber; i++){
        delete [] edges[i];
    }
    delete [] edges;
    delete [] vertices;
}

void Graph::printGraph(){

    for(int i = 0; i < verticesNumber; i++){
        for(int j = 0; j < verticesNumber; j++){
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printGraphList(){

    for(int i = 0; i < verticesNumber; i++){
        cout << i << " -> ";
        for(int j = 0; j < verticesNumber; j++){
            if(edges[i][j] != -1)
                cout << j << "("<< edges[i][j] << ")  ";
        }
        cout << endl;
    }
}

void Graph::printVertexWeight(){

    for(int i = 0; i < verticesNumber; i++){
        cout << vertices[i] << endl;
    }
}

void Graph::printGroupsBounds(){
    for(int i = 0; i < groupsNumber; i++){
        for(int j = 0; j < 2; j++){
            cout << groupsBounds[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::insertEdge(int vertexOne, int vertexTwo, int edgeWeight){

    edges[vertexOne][vertexTwo] = edgeWeight;
    edges[vertexTwo][vertexOne] = edgeWeight;
}

void Graph::readFile(char fileName []){

    ifstream txtFile;
    txtFile.open(fileName);

    if(!txtFile){
        cout << "File not found!" << endl;
        exit(0);
    }

    string graphInfoAux;//read the first line
    string graphSizeAux;//number of vertices
    string groupSizeAux;//number of groups
    string lowerBoundAux;// lower bound group
    string upperBoundAux;// upper bound group
    string vertexWeightAux;// weight of vertex
    string trash;// W - file
    string vertexOneAux;// first vertex
    string vertexTwoAux;// second vertex
    string edgeWeightAux;// edge weight

    string groupType;

    getline(txtFile,graphInfoAux);
    stringstream line(graphInfoAux);//change to stringstream

    ///read number of elements and group
    line >> graphSizeAux >> groupSizeAux >> groupType;
    verticesNumber = atoi((char*)graphSizeAux.c_str());
    groupsNumber = atoi((char*)groupSizeAux.c_str());

    ///Initialize the groupsNumber array
    groupsBounds = new int*[groupsNumber];
    for(int j = 0; j < groupsNumber; j++){
        groupsBounds[j] = new int[2];
    }

    ///Initialize the vertices array and edges matrix with -1
    vertices = new int[verticesNumber];
    edges = new int*[verticesNumber];
    for(int i = 0; i < verticesNumber; i++){
        edges[i] = new int[verticesNumber];
        vertices[i] = -1;
        for(int j = 0; j < verticesNumber; j++){
            edges[i][j] = -1;
        }
    }

    ///setting the lower and upper bound to the array
    int i = 0;
    while(i < groupsNumber){
        line >> lowerBoundAux >> upperBoundAux;
        groupsBounds[i][0] = atoi((char*)lowerBoundAux.c_str());
        groupsBounds[i][1] = atoi((char*)upperBoundAux.c_str());
        i++;
    }

    ///reading W from the file
    line >> trash;

    ///setting the weight of the vertices to the array
    i = 0;
    while(i < verticesNumber){
        line >> vertexWeightAux;
        vertices[i] = atoi((char*)vertexWeightAux.c_str());
        i++;
    }

    while(getline(txtFile, graphInfoAux)){
        stringstream line(graphInfoAux);

        line >> vertexOneAux >> vertexTwoAux >> edgeWeightAux;
        int vertexOne = atoi((char*)vertexOneAux.c_str());
        int vertexTwo = atoi((char*)vertexTwoAux.c_str());
        int edgeWeight = atoi((char*)edgeWeightAux.c_str());

        insertEdge(vertexOne,vertexTwo,edgeWeight);
    }

    txtFile.close();
}

