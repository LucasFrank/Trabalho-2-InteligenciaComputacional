#include <iostream>
#include "Graph.h"
#include <time.h>

using namespace std;

char* formatString(char fileName [], bool firstBest, bool randomLS, bool randomInitialSolution){
    char folder [20]  = "output4/";

    char fb [2];
    char rLS [2];
    char rIS [2];
    fb[0] = firstBest == true ? '1' : '0';
    rLS[0] = randomLS == true ? '1' : '0';
    rIS[0] = randomInitialSolution == true ? '1' : '0';
    fb[1] = '\0';
    rLS[1] = '\0';
    rIS[1] = '\0';


    char* aux = new char[50];
    aux[0] = '\0';
    char* auxFileName = new char[50];
    int i = 0;
    while(fileName[i] != '.'){
        auxFileName[i] = fileName[i];
        i++;
    }
    auxFileName[i] = '\0';

    strcat(aux,folder);
    strcat(aux,auxFileName);
    strcat(aux,fb);
    strcat(aux,rLS);
    strcat(aux,rIS);
    char results [] = "output.txt";
    strcat(aux,results);

    return aux;
}

vector<string> fileNameFolder(){
    vector<string> fileNames;

    fileNames.push_back("DCC136-82_01.txt");
    fileNames.push_back("DCC136-82_02.txt");
    fileNames.push_back("DCC136-82_03.txt");
    fileNames.push_back("DCC136-82_04.txt");
    fileNames.push_back("DCC136-82_05.txt");

    fileNames.push_back("DCC136-240_01.txt");
    fileNames.push_back("DCC136-240_02.txt");
    fileNames.push_back("DCC136-240_03.txt");
    fileNames.push_back("DCC136-240_04.txt");
    fileNames.push_back("DCC136-240_05.txt");

    fileNames.push_back("DCC136-480_01.txt");
    fileNames.push_back("DCC136-480_02.txt");
    fileNames.push_back("DCC136-480_03.txt");
    fileNames.push_back("DCC136-480_04.txt");
    fileNames.push_back("DCC136-480_05.txt");

    fileNames.push_back("20_5_A.txt");
    fileNames.push_back("20_5_B.txt");
    fileNames.push_back("30_5_A.txt");
    fileNames.push_back("30_5_B.txt");
    fileNames.push_back("30_10_A.txt");
    fileNames.push_back("30_10_B.txt");
    fileNames.push_back("40_5_A.txt");
    fileNames.push_back("40_5_B.txt");
    fileNames.push_back("40_10_A.txt");
    fileNames.push_back("40_10_B.txt");
    fileNames.push_back("100_15_A.txt");
    fileNames.push_back("100_15_B.txt");
    fileNames.push_back("100_25_A.txt");
    fileNames.push_back("100_25_B.txt");
    fileNames.push_back("200_25_A.txt");
    fileNames.push_back("200_25_B.txt");

    return fileNames;
}

int main(){
    srand(time(NULL));
    vector<string> fileNames = fileNameFolder();
    unsigned int i = 0;
    while(i < fileNames.size()){
        char filePath [100] = "input";
        char folder [10] = "/";
        char fileName [50];              ///  "/"  "/TipoA/"  "/TipoB/"  "/TipoC/" "/TipoD/"
        strcpy(fileName, fileNames.at(i).c_str());/// InstancesInput/instanciaExemplo.txt      A -> DCC136-82_01.txt    B -> DCC136-240_01   C -> DCC136-480_01    D->  200_25_A.txt
        char fileType = fileName[0] != 'D' ? 'D' : 'A';

        strcat(filePath,folder);
        strcat(filePath,fileName);
        Graph* g = new Graph(filePath,fileType);
        g->calculateTotalEdgeWeightVerification();

        //g->printVertexWeight();
        //g->printGroupsBounds();
        //g->printGraph();
        //g->printGraphList();

        bool firstBest = true;
        bool randomLS = true;
        bool randomInitialSolution = true;
        int time = 60;

        ofstream out;
        char* results = formatString(fileName,firstBest,randomLS,randomInitialSolution);
        out.open(results,fstream::out);

        //g->runGreedyAlgorithm();
        g->runLocalSearchAlgorithm(firstBest, randomLS, randomInitialSolution, time,&out);

        out.close();
        delete g;
        cout << i << endl;
        i++;
    }
    return 0;
}
