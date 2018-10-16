#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    char filePath [100] = "InstancesInput";
    char folder [10] = "/TipoD/";              ///  "/"  "/TipoA/"  "/TipoB/"  "/TipoC/" "/TipoD/"
    char fileName [] = "200_25_A.txt";   /// InstancesInput/instanciaExemplo.txt      A -> DCC136-82_01.txt    B -> DCC136-240_01   C -> DCC136-480_01    D->  200_25_A.txt
    char fileType = folder[6] != '/' ? 'A' : folder[5];
    strcat(filePath,folder);
    strcat(filePath,fileName);

    Graph* g = new Graph(filePath,fileType);

    //cout << "Vertex Weight: " << endl;
    //g->printVertexWeight();
    cout << endl << "Groups Bounds: " << endl;
    g->printGroupsBounds();
    cout << endl;
    //g->printGraph();
    cout << "Graph List: " << endl;
    g->printGraphList();

    g->runGreedyAlgorithm();

    delete g;

    return 0;
}
