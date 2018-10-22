#include "Graph.h"

#define SWAP(sol, group1, element1, group2, element2){\
            int temp = sol[group1][element1];\
            sol[group1][element1] = sol[group2][element2];\
            sol[group2][element2] = temp;}
#define VERIFY_VIABILITY(sol, group)({\
            float weight = calculateVertexGroupWeight(sol[group]);\
            weight <= groupsBounds[group][1] && weight >= groupsBounds[group][0];})
#define VERIFY_TIME(clockIni, time)({\
            time == 0 ? \
            1 : (clock()-clockIni)/(float)CLOCKS_PER_SEC < time;})
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

    cout << endl << "Graph 2D-Array: " << endl;
    for(int i = 0; i < verticesNumber; i++){
        for(int j = 0; j < verticesNumber; j++){
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printGraphList(){

    cout << endl << "Graph List: " << endl;
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

    cout << endl << "Vertex Weight: " << endl;
    for(int i = 0; i < verticesNumber; i++){
        cout << vertices[i] << " ";
    }
    cout << endl;
}

void Graph::printGroupsBounds(){

    cout << endl << "Groups Bounds: " << endl;
    for(int i = 0; i < groupsNumber; i++){
        for(int j = 0; j < 2; j++){
            cout << groupsBounds[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printSolution(vector< vector<int> > sol){
    cout << endl << "S = {";
    for(unsigned int i = 0; i < sol.size(); i++){
        vector<int> currentGroup = sol.at(i);
        cout << "{ ";
        for(unsigned int j = 0; j < currentGroup.size(); j++){
            if(j == currentGroup.size() - 1)
                cout << currentGroup.at(j) << "";
            else
                cout << currentGroup.at(j) << ", ";
        }
        if(i == sol.size() - 1)
            cout << "}";
        else
            cout << "},";
    }
    cout << "}" << endl;;
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

bool Graph::isCover(int* verticesAux){

    for(int i = 0; i < verticesNumber; i++){
        if(verticesAux[i] == 0)
            return false;
    }
    return true;
}

bool Graph::forcedStopCondition(int* groupsAux){
    for(int i = 0; i < groupsNumber; i++){
        if(groupsAux[i] != -1)
            return false;
    }
    return true;
}

bool Graph::verifyBounds(vector< vector<int> > sol){

    for(unsigned int i = 0; i < sol.size(); i++){
        vector<int> currentGroup = sol.at(i);
        int weight = 0;
        for(unsigned int j = 0; j < currentGroup.size(); j++){
            weight += vertices[currentGroup.at(j)];
        }
        if(weight < groupsBounds[i][0] || weight > groupsBounds[i][1]){
            return false;
        }
    }
    return true;
}

bool Graph::verifyEdges(int vertex){
    for(int i = 0; i < verticesNumber; i++){
        if(edges[vertex][i] != 0)
            return true;
    }
    return false;
}

int Graph::getVertexEdgeWeight(int vertex){

    float weight = 0;
    for(int i = 0; i < verticesNumber; i++){
        weight += edges[vertex][i];
    }
    return weight;
}

int Graph::getVertex(int* vert){

    for(int i = 0; i < verticesNumber; i++){
        if(vert[i] == 0)
            return i;
    }
    return -1;
}

int Graph::getVertexByWeight(int* vert){

    float weight = 0;
    int vertexIndex = -1;
    for(int i = 0; i < verticesNumber; i++){
        if(vert[i] == 0)
            if(vertices[i] > weight){
                weight = vertices[i];
                vertexIndex = i;
            }
    }
    return vertexIndex;
}

int Graph::getVertexNeighbor(int* vert, int vertexValue){

    if(vertexValue == -1)
        return -1;

    for(int i = 0; i < verticesNumber; i++){
        if(edges[vertexValue][i] != 0){
            if(vert[i] != 1){
                return i;
            }
        }
    }
    return -1;
}

vector<int> Graph::getNeighborhood(vector<int> group){

    vector<int> neighborhood;
    for(unsigned int i = 0; i < group.size(); i++){
        int vertexAux = group.at(i);
        for(int j = 0; j < verticesNumber; j++){
            if(edges[vertexAux][j] != 0 && !(find(group.begin(),group.end(),j) != group.end()) && !(find(neighborhood.begin(),neighborhood.end(),j) != neighborhood.end()))
                neighborhood.push_back(j);
        }
    }

    return neighborhood;
}

int Graph::getVertexByWeightNeighbor(int* vert,vector<int> group){

    int vertexIndex = -1;
    float weight = 0;

    for(unsigned int i = 0; i < group.size(); i++){
        int vertexAux = group.at(i);
        for(int j = 0; j < verticesNumber; j++){
            if(edges[vertexAux][j] != 0){
                if(vert[j] == 0 && vertices[j] > weight){
                    weight = vertices[j];
                    vertexIndex = j;
                }
            }
        }
    }

    return vertexIndex;
}

int Graph::getVertexByWeightNeighbor(int* vert,vector<int> group,vector<int> fail){

    int vertexIndex = -1;
    float weight = 0;

    for(unsigned int i = 0; i < group.size(); i++){
        int vertexAux = group.at(i);
        for(int j = 0; j < verticesNumber; j++){
            if(edges[vertexAux][j] != 0){
                if(!(find(fail.begin(),fail.end(),j) != fail.end()) && vert[j] == 0 && edges[vertexAux][j] > weight){
                    weight = edges[vertexAux][j];
                    vertexIndex = j;
                }
                /*if(!(find(fail.begin(),fail.end(),j) != fail.end()) && vert[j] == 0 && vertices[j] > weight){
                    weight = vertices[j];
                    vertexIndex = j;
                }*/
            }
        }
    }

    return vertexIndex;
}

void Graph::setVertexCoverWithNoEdges(int* verticesCover){

    for(int i = 0; i < verticesNumber; i++){
        if(!verifyEdges(i)){
            verticesCover[i] = 1;
        }
    }
}

vector< vector<int> > Graph::greedyHeuristic(){

    vector< vector<int> > solution(groupsNumber); /// to store the solution
    int* verticesCover = new int[verticesNumber]; /// to keep track of which vertex that was checked
    for(int i = 0; i < verticesNumber; i++)
        verticesCover[i] = 0;

    int* currentWeightGroup = new int[groupsNumber]; /// to store each weight of each group
    int* currentVertex = new int[groupsNumber];
    for(int i = 0; i < groupsNumber; i++){
        currentWeightGroup[i] = 0;
        currentVertex[i] = -1;
    }

    vector< vector<int> > failed(groupsNumber); /// to store the vertices that failed to insert into a group


    while(!isCover(verticesCover)){
        for(unsigned int i = 0; i < solution.size(); i++){
            if(solution[i].size() == 0){
                currentVertex[i] = getVertexByWeight(verticesCover);
                solution[i].push_back(currentVertex[i]);
                verticesCover[currentVertex[i]] = 1;
                currentWeightGroup[i] += vertices[currentVertex[i]];
            }else{
                currentVertex[i] = getVertexByWeightNeighbor(verticesCover,solution[i],failed[i]);
                if(currentVertex[i] == -1)
                    currentVertex[i] = getVertexByWeight(verticesCover);

                if(currentVertex[i] != -1 && currentWeightGroup[i] + vertices[currentVertex[i]] <= groupsBounds[i][1]){
                    solution[i].push_back(currentVertex[i]);
                    verticesCover[currentVertex[i]] = 1;
                    currentWeightGroup[i] += vertices[currentVertex[i]];
                }else if(currentVertex[i] != -1 && currentWeightGroup[i] + vertices[currentVertex[i]] > groupsBounds[i][1]){
                    failed[i].push_back(currentVertex[i]);
                }
            }
        }
    }

    delete currentVertex;
    delete currentWeightGroup;
    delete verticesCover;
    return solution;
}

void Graph::runGreedyAlgorithm(){

    vector< vector<int> > solution = greedyHeuristic();

    ///Printing
    cout << endl << "Greedy Solution: " << endl;
    for(unsigned int i = 0; i < solution.size(); i++){
        vector<int> currentGroup = solution.at(i);
        cout << i << ": ";
        for(unsigned int j = 0; j < currentGroup.size(); j++){
            cout << currentGroup.at(j) << " ";
        }
        cout << endl;
    }

    if(!verifyBounds(solution))
        cout << endl << "Solution is not within bounds." << endl;
    else
        cout << endl << "Bounds working." << endl;

    cout << "TotalWeight " << calculateTotalEdgeWeight(solution) << endl;
}

vector< vector<int> > Graph::randomizeSolution(vector< vector<int> > sol){

    for(int i = 0; i < groupsNumber; i++){
        for(unsigned j = 0; j < sol[i].size(); j++){
            for(int l = i + 1; l < groupsNumber - 1; l++){
                for(unsigned k = 0; k < sol[l].size(); k++){
                    float random = rand() % 100;
                    if(random > 50){
                        SWAP(sol,i,j,l,k);
                        if(!(VERIFY_VIABILITY(sol, l) && VERIFY_VIABILITY(sol, i)))
                            SWAP(sol,i,j,l,k);
                    }
                }
            }
        }
    }

    return sol;
}

float Graph::calculateTotalEdgeWeight(vector< vector<int> > sol){

    float totalWeight = 0;
    for(unsigned int i = 0; i < sol.size(); i++){
        vector<int> alreadyUsed;
        vector<int> currentGroup = sol.at(i);
        for(unsigned int j = 0; j < currentGroup.size(); j++){
            for(unsigned int k = 0; k < currentGroup.size(); k++){
                if(!(find(alreadyUsed.begin(),alreadyUsed.end(),currentGroup.at(k)) != alreadyUsed.end())){
                    alreadyUsed.push_back(currentGroup.at(j));
                    totalWeight += edges[currentGroup.at(j)][currentGroup.at(k)];
                }
            }
        }
    }
    return totalWeight;
}

vector< vector<int> > Graph::localSearch(bool firstBest, bool randomGreedy, int timeLimit){

    vector<vector<int> > solution = greedyHeuristic();
    if(randomGreedy)
        solution = randomizeSolution(solution);

    vector<vector<int> > partialSolution;
    vector<vector<int> > auxSolution;
    vector<vector<int> > groupAux;
    float bestSolutionWeight, initialWeight1 = 0, initialWeight2 = 0, partialSolutionWeight = 0, auxSolutionWeight = 0;
    bestSolutionWeight = calculateTotalEdgeWeight(solution);
    unsigned groupNum = solution.size() - 1;
    unsigned groupSize = 0;
    unsigned localGroupSize = 0;
    bool breakAll = false;
    clock_t clockIni = clock();
    while(VERIFY_TIME(clockIni, timeLimit)){
        for(unsigned i = 0; i < groupNum && !breakAll; i++){
            groupSize = solution[i].size();
            for(unsigned j = 0; j < groupSize && !breakAll; j++){
                auxSolution = solution;
                for(unsigned l = i + 1; l < groupNum && !breakAll; l++){
                    localGroupSize = solution[l].size();
                    for(unsigned k = 0; k < localGroupSize && !breakAll; k++){
                        groupAux.clear();
                        groupAux.push_back(auxSolution[i]);
                        initialWeight1 = calculateTotalEdgeWeight(groupAux);
                        groupAux.clear();
                        groupAux.push_back(auxSolution[l]);
                        initialWeight2 = calculateTotalEdgeWeight(groupAux);
                        auxSolutionWeight = bestSolutionWeight;
                        SWAP(auxSolution,i,j,l,k)
                        if(VERIFY_VIABILITY(auxSolution, l) && VERIFY_VIABILITY(auxSolution, i)){
                            auxSolutionWeight -= (initialWeight1 + initialWeight2);
                            groupAux.clear();
                            groupAux.push_back(auxSolution[i]);
                            initialWeight1 = calculateTotalEdgeWeight(groupAux);
                            groupAux.clear();
                            groupAux.push_back(auxSolution[l]);
                            initialWeight2 = calculateTotalEdgeWeight(groupAux);
                            auxSolutionWeight += (initialWeight1 + initialWeight2);
                            if(auxSolutionWeight > partialSolutionWeight){
                                partialSolutionWeight = auxSolutionWeight;
                                partialSolution = auxSolution;
                                if(firstBest) breakAll = true;
                            }
                        }
                        SWAP(auxSolution,i,j,l,k)
                    }
                }
            }
        }
        if(partialSolutionWeight > bestSolutionWeight){
            bestSolutionWeight = partialSolutionWeight;
            solution = partialSolution;
            partialSolutionWeight = 0;
        }
        breakAll = false;
    }
    return solution;
}

void Graph::runLocalSearchAlgorithm(bool firstBest, bool random, bool randomGreedy, int timeLimit,ofstream *out){

    vector<vector<int> > l;
    vector<vector<int> > bestSolution;
    float weight = 0;
    float bestWeight = 0;
    float mean = 0;

    int numberOfIteration = 10; /// Iterations Number
    int i = 0;
    while(i < numberOfIteration){
        if(random){
            l = localSearchRandom(randomGreedy,timeLimit);
        }else{
            l = localSearch(firstBest,randomGreedy, timeLimit);
        }
        weight = calculateTotalEdgeWeight(l);
        mean += weight;
        if(weight > bestWeight){
            bestWeight = weight;
            bestSolution = l;
        }

        i++;
    }
    mean = mean/float(numberOfIteration);
    printSolution(bestSolution);
    cout << "LocalSearch Best Weight: " << bestWeight << endl;
    cout << "Mean: " << mean << endl;
    if(verifyBounds(bestSolution)){
        cout << "Bounds Ok." << endl;
    }else{
        cout << "Bounds not Ok." << endl;
    }
    writeFile(out,firstBest,random,randomGreedy,bestWeight,mean,bestSolution);
}

float Graph::calculateVertexGroupWeight(vector<int>group){

    float weight = 0;
    for(unsigned i = 0; i < group.size(); i++){
        weight += vertices[group[i]];
    }
    return weight;
}

vector<vector<int> > Graph::localSearchRandom(bool randomGreedy, int timeLimit){

    vector<vector<int> > solution = greedyHeuristic();
    if(randomGreedy)
        solution = randomizeSolution(solution);

    vector<vector<int> > groupAux;
    float bestSolutionWeight, initialWeight1 = 0, initialWeight2 = 0, partialSolutionWeight = 0;
    bestSolutionWeight = calculateTotalEdgeWeight(solution);
    clock_t clockIni = clock();
    unsigned i = 0, j = 0, k = 0, l = 0;
    unsigned groupNum = solution.size();
    while(VERIFY_TIME(clockIni, timeLimit)){
        i = rand() % groupNum;
        j = rand() % solution[i].size();
        k = rand() % groupNum;
        while(k == i) k = rand() % groupNum;
        l = rand() % solution[k].size();

        groupAux.clear();
        groupAux.push_back(solution[i]);
        initialWeight1 = calculateTotalEdgeWeight(groupAux);
        groupAux.clear();
        groupAux.push_back(solution[k]);
        initialWeight2 = calculateTotalEdgeWeight(groupAux);
        partialSolutionWeight = bestSolutionWeight;
        SWAP(solution,i,j,k,l)
        if(VERIFY_VIABILITY(solution, k) && VERIFY_VIABILITY(solution, i)){
            partialSolutionWeight -= (initialWeight1 + initialWeight2);
            groupAux.clear();
            groupAux.push_back(solution[i]);
            initialWeight1 = calculateTotalEdgeWeight(groupAux);
            groupAux.clear();
            groupAux.push_back(solution[k]);
            initialWeight2 = calculateTotalEdgeWeight(groupAux);
            partialSolutionWeight += (initialWeight1 + initialWeight2);
            if(partialSolutionWeight > bestSolutionWeight){
                bestSolutionWeight = partialSolutionWeight;
            }else{
                SWAP(solution,i,j,k,l)
            }
        }else{
            SWAP(solution,i,j,k,l)
        }
    }
    return solution;
}

void Graph::writeFile(ofstream *out, bool firstBest, bool random, bool randomGreedy, float bestWeight, float mean, vector< vector<int> > sol){

    *out << "Result" << endl;
    *out << "Best Weight: " << bestWeight << endl;
    *out << "Mean: " << mean << endl;
    *out << "Solution: ";
    *out << "S = {";
    for(unsigned int i = 0; i < sol.size(); i++){
        vector<int> currentGroup = sol.at(i);
        *out << "{ ";
        for(unsigned int j = 0; j < currentGroup.size(); j++){
            if(j == currentGroup.size() - 1)
                *out << currentGroup.at(j) << "";
            else
                *out << currentGroup.at(j) << ", ";
        }
        if(i == sol.size() - 1)
            *out << "}";
        else
            *out << "},";
    }
    *out << "}" << endl;;
}

void Graph::calculateTotalEdgeWeightVerification(){
    float weight = 0;
    for(int i = 0; i < verticesNumber; i++){
        for(int j = 0; j < verticesNumber; j++){
            if(i <= j){
                weight += edges[i][j];
            }
        }
    }
    cout << fixed;
    cout << "Total weight in edges: " << weight << endl;
}
