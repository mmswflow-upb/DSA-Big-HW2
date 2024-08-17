#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

template<typename TnodeInfo, typename TedgeInfo>class DiGraph {
public:
    int N;
    char** A;
    TnodeInfo* nodeInfo;
    TedgeInfo** edgeInfo;

    DiGraph(int numNodes) {
        int i, j;

        N = numNodes;

        /// allocate the adjacency matrix
        A = new char* [N]; ///allocated rows
        for (i = 0; i < N; i++)
            A[i] = new char[N]; ///allocated columns

        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                A[i][j] = 0;

        // allocate the array with node information
        nodeInfo = new TnodeInfo[N];

        // allocate the matrix of edge information
        edgeInfo = new TedgeInfo * [N];
        for (i = 0; i < N; i++)
            edgeInfo[i] = new TedgeInfo[N];
    }

    void setNodeInfo(int i, TnodeInfo info) {
        nodeInfo[i] = info;
    }

    TnodeInfo getNodeInfo(int i) {
        return nodeInfo[i];
    }

    void addEdge(int i, int j) {
        A[i][j] = 1;
    }
   
    void removeEdge(int i, int j) {
        A[i][j] = 0;
    }

    void setEdgeInfo(int i, int j, TedgeInfo info) {
        edgeInfo[i][j] = info;
    }

    TedgeInfo getEdgeInfo(int i, int j) {
        return edgeInfo[i][j];
    }

    int findInfo(TnodeInfo x) {

        for (int i = 0; i < N; i++) {
            if (nodeInfo[i] == x) {
                return i;
            }
        }
        return -1;
    }

    ~DiGraph() {
        int i;
        for (i = 0; i < N; i++) {
            delete A[i];
            delete edgeInfo[i];
        }
        delete A;
        delete edgeInfo;
        delete[] nodeInfo;
    }
};

template <typename TnodeInfo, typename TedgeInfo> 
DiGraph<TnodeInfo, TedgeInfo>* expandDiGraph(DiGraph<TnodeInfo, TedgeInfo>* oldGraph, char x) {

    int i = 0;
    DiGraph<TnodeInfo, TedgeInfo>* res = new DiGraph<TnodeInfo, TedgeInfo>(oldGraph->N + 1);

    for ( i; i < oldGraph->N; i++) {
        res->setNodeInfo(i,oldGraph->getNodeInfo(i));
        res->A[i] = oldGraph->A[i];
    }
    res->setNodeInfo(i, x);
  
    return res;
}

template <typename TnodeInfo, typename TedgeInfo>
void topologicalSortTraversal(DiGraph<TnodeInfo, TedgeInfo>* g, stack<char> *sequence, char* visited, int indx) {

    visited[indx] = 1;

    for (int i = 0; i < g->N; i++) {
        if (g->A[indx][i] == 1 && visited[i] == 0) {//Calls topSortTraversal  for all unvisited neighbors
            topologicalSortTraversal(g, sequence, visited, i);
        }
    }
    sequence->push(g->getNodeInfo(indx));
}

template <typename TnodeInfo, typename TedgeInfo>
void topologicalSort(DiGraph<TnodeInfo, TedgeInfo>* g, stack<char>* sequence, char* visited) {

    for (int i = 0; i < g->N; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < g->N; i++) {

        if (visited[i] == 0) {

            topologicalSortTraversal(g, sequence, visited, i);
        }
    }
}

template <typename TnodeInfo, typename TedgeInfo>
void displayResult(DiGraph<TnodeInfo, TedgeInfo>* g, string outputPath) {

    ofstream fileWriter;

    fileWriter.open(outputPath);
   
    if (fileWriter.fail()) {

        cout << "Error opening the output file. \n\n";
        return;
    }

    if (g->N <= 1) {
        return;
    }

    fileWriter << "Displaying Graph Connections: \n\n";

    for (int i = 0; i < g->N; i++) {
        for (int v = 0; v < g->N; v++) {
            if (g->A[i][v] == 1) {
                
               fileWriter << g->getNodeInfo(i) << " -> " << g->getNodeInfo(v) << "\n";
            }
        }
    }

    fileWriter << "\n\nDisplaying Correct Order of Characters: ";
    
    stack<char> *sequence = new stack<char>; 
    char* visited = new char[g->N];
    
    topologicalSort(g, sequence, visited);

    while (!sequence->empty()) {
        fileWriter << sequence->top() << " ";
        sequence->pop();
    }
    fileWriter.close();
}

int main() {

   DiGraph<char, int>* g = new DiGraph<char, int>(0);

   string path, path2, line;
   int k = 50;//Maximum number of words/ non-empty lines
   cout << "Insert a path to an input file: ";
   cin >> path;
   
   cout << "\n\nInsert a path to an output file: ";
   cin >> path2;
   cout << "\n\n";

   ifstream fileReader;
   ofstream fileWriter;

   queue<string> words;

   fileReader.open(path);

   if (fileReader.fail()) {

       cout << "ERROR WHEN OPENING THE INPUT FILE.\n\n";
       return 1;
   }

   while ((getline(fileReader, line)) && k > 0) {

       if (line == ".") {
           break;
       }
       if (line == "") {
           continue;
       }    
       k--;
       words.push(line);
   }
   fileReader.close();

   if (words.size() == 1) {

       
       fileWriter.open(path2);

       if (fileWriter.fail()) {

           cout << "ERROR OPENING THE OUTPUT FILE. \n\n";
           return 1;
       }

       fileWriter << "Displaying Correct Order of Characters: " << words.front()[0] << "\n";

       fileWriter.close();

       return 0;
   }//Case with only one word as input.
   else if (words.size() == 0) {

       fileWriter.open(path2);

       if (fileWriter.fail()) {

           cout << "ERROR OPENING THE OUTPUT FILE. \n\n";
           return 1;
       }
       fileWriter << "No Valid Input Provided. \n\n";
       fileWriter.close();
       return 0;

   }//Case with 0 input 

   while (words.size() > 1) {//We start comparing the words from the stack until we dont have more than 1 elm

       string temp1 = words.front();
       words.pop();
       string temp2 = words.front();

       for (int i = 0; i < min(temp1.length(), temp2.length()); i++) {//We check for the smallest length

           if (temp1[i] != temp2[i]) {//ana
               //ianod 
               //a->i

               int indx1 = g->findInfo(temp1[i]);
               int indx2 = g->findInfo(temp2[i]);

               if (indx1 == -1 && indx2 == -1) {//They both don't exist in the graph

                   g = expandDiGraph(g, temp1[i]);
                   g = expandDiGraph(g, temp2[i]);
               }
               else if (indx1 != -1 && indx2 == -1) {//temp1 exists and temp2 doesn't

                   g = expandDiGraph(g, temp2[i]);
               }
               else if (indx1 == -1 && indx2 != -1) {//Temp1 doesn't exist and temp2 does

                   g = expandDiGraph(g, temp1[i]);
               }

               indx1 = g->findInfo(temp1[i]);
               indx2 = g->findInfo(temp2[i]);

               if (g->A[indx1][indx2]  == 1 || g->A[indx2][indx1] == 1) {
                   break;
               }

               g->addEdge(indx1, indx2);
            
               break;
           }
       }
   }
   displayResult(g,path2);
}