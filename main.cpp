#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    char filePath [100] = "InstancesInput";
    char folder [] = "/TipoA/";              ///  "/"
    char fileName [] = "DCC136-82_05.txt";   /// InstancesInput/instanciaExemplo.txt      A-> DCC136-82_05.txt    D->  200_25_A.txt
    char fileType = folder[5];
    strcat(filePath,folder);
    strcat(filePath,fileName);

    Graph* g = new Graph(filePath,fileType);
    int test;
    g->printVertexWeight();
    cout << endl;
    g->printGroupsBounds();
    cout << endl;
    cin >> test;
    g->printGraph();
    cout << endl;
    g->printGraphList();

    delete g;

    return 0;
}
