#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    char filePath [100] = "InstancesInput";
    char folder [] = "/TipoA/";              ///  "/"
    char fileName [] = "DCC136-82_05.txt";   /// InstancesInput/instanciaExemplo.txt       DCC136-82_05.txt
    strcat(filePath,folder);
    strcat(filePath,fileName);

    Graph* g = new Graph(filePath);

    g->printVertexWeight();
    cout << endl;
    g->printGroupsBounds();
    cout << endl;
    g->printGraph();
    cout << endl;
    g->printGraphList();

    delete g;

    return 0;
}
