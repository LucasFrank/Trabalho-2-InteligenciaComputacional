#include "Graph.h"


Graph::Graph(char fileName [], char readType){

    readFile(fileName,readType);
}

Graph::~Graph(){

    for(int i = 0; i < verticesNumber; i++){
        delete [] edges[i];
    }
    delete [] edges;
    delete [] vertices;
    for(int i = 0; i < groupsNumber; i++){
        delete [] groupsBounds[i];
    }
    delete [] groupsBounds;
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
        cout << i << "(" << vertices[i] << ")" <<" -> ";
        for(int j = 0; j < verticesNumber; j++){
            if(edges[i][j] != 0)
                cout << j << "("<< edges[i][j] << ")  ";
        }
        cout << endl;
    }
}

void Graph::printVertexWeight(){

    for(int i = 0; i < verticesNumber; i++){
        cout << vertices[i] << " ";
    }
    cout << endl;
}

void Graph::printGroupsBounds(){

    for(int i = 0; i < groupsNumber; i++){
        for(int j = 0; j < 2; j++){
            cout << groupsBounds[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::insertEdge(int vertexOne, int vertexTwo, float edgeWeight){

    edges[vertexOne][vertexTwo] = edgeWeight;
    edges[vertexTwo][vertexOne] = edgeWeight;
}

void Graph::readFile(char fileName [], char readType){

    ifstream txtFile;
    txtFile.open(fileName);

    if(!txtFile){
        cout << "File not found!" << endl;
        exit(0);
    }

    if(readType == 'A' || readType == 'B' || readType == 'C'){
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
        groupsBounds = new float*[groupsNumber];
        for(int j = 0; j < groupsNumber; j++){
            groupsBounds[j] = new float[2];
        }

        ///Initialize the vertices array and edges 2d-Array with 0
        vertices = new float[verticesNumber];
        edges = new float*[verticesNumber];
        for(int i = 0; i < verticesNumber; i++){
            edges[i] = new float[verticesNumber];
            vertices[i] = 0;
            for(int j = 0; j < verticesNumber; j++){
                edges[i][j] = 0;
            }
        }

        ///setting the lower and upper bound to the array
        int i = 0;
        while(i < groupsNumber){
            line >> lowerBoundAux >> upperBoundAux;
            groupsBounds[i][0] = atof((char*)lowerBoundAux.c_str());
            groupsBounds[i][1] = atof((char*)upperBoundAux.c_str());
            i++;
        }

        ///reading W from the file
        line >> trash;

        ///setting the weight of the vertices to the array
        i = 0;
        while(i < verticesNumber){
            line >> vertexWeightAux;
            vertices[i] = atof((char*)vertexWeightAux.c_str());
            i++;
        }

        /// reading each line and inserting vertices and their weights into the 2d-Array
        while(getline(txtFile, graphInfoAux)){
            stringstream line(graphInfoAux);

            line >> vertexOneAux >> vertexTwoAux >> edgeWeightAux;
            int vertexOne = atoi((char*)vertexOneAux.c_str());
            int vertexTwo = atoi((char*)vertexTwoAux.c_str());
            float edgeWeight = atof((char*)edgeWeightAux.c_str());

            insertEdge(vertexOne,vertexTwo,edgeWeight);
        }

    }else if(readType == 'D'){
        string graphInfoAux;//read the first line
        string edgeWeightAux;// edge weight

        ///read number of elements and group
        getline(txtFile,graphInfoAux);
        verticesNumber = atoi((char*)graphInfoAux.c_str());

        getline(txtFile,graphInfoAux);
        groupsNumber = atoi((char*)graphInfoAux.c_str());

        ///Initialize the groupsNumber array
        groupsBounds = new float*[groupsNumber];
        for(int j = 0; j < groupsNumber; j++){
            groupsBounds[j] = new float[2];
        }

        ///Initialize the vertices array and edges 2d-Array with 0
        vertices = new float[verticesNumber];
        edges = new float*[verticesNumber];
        for(int i = 0; i < verticesNumber; i++){
            edges[i] = new float[verticesNumber];
            vertices[i] = 0;
            for(int j = 0; j < verticesNumber; j++){
                edges[i][j] = 0;
            }
        }

        getline(txtFile,graphInfoAux);
        ///setting the lower and upper bound to the array
        int i = 0;
        while(i < groupsNumber){
            groupsBounds[i][0] = 0.0;
            groupsBounds[i][1] = atof((char*)graphInfoAux.c_str());
            i++;
        }

        ///setting the weight of the vertices to the array
        i = 0;
        while(i < verticesNumber){
            getline(txtFile,graphInfoAux);
            vertices[i] = atof((char*)graphInfoAux.c_str());
            i++;
        }

        i = 0;
        int j = 0;
        ///reading the file and inserting into the 2d-array
        getline(txtFile,graphInfoAux);
        stringstream line(graphInfoAux);
        while(i < verticesNumber){
            j = 0;
            while(j < verticesNumber){
                line >> edgeWeightAux;
                float edgeWeight = atof((char*)edgeWeightAux.c_str());
                insertEdge(i,j,edgeWeight);
                j++;
            }
            i++;
        }

    }


    txtFile.close();

}

