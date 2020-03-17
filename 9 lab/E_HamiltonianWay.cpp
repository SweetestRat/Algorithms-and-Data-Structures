#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ifstream fin ("hamiltonian.in");
ofstream fout ("hamiltonian.out");

void TopSort(int vertex, vector<vector<int>> &AdjacencyList, vector<int> &Stack, vector<int> &visited)
{
    visited[vertex] = 1;

    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(visited[AdjacencyList[vertex][i]] == 1)
            continue;
        TopSort(AdjacencyList[vertex][i], AdjacencyList, Stack, visited);
    }
    Stack.push_back(vertex);
}

int main()
{
    int numV, numE;
    int col1, col2;

    fin >> numV >> numE;

    vector<vector<int>> AdjacencyList (numV + 1, vector<int>());
    vector<int> visited (numV + 1, 0);
    vector<int> Stack;
    map<pair<int, int>, bool> check;


    for(int i = 0; i < numE; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);

        check[pair<int, int>(col1, col2)] = true;
    }

    for(int vertex = 1; vertex <= numV; ++vertex)
    {
        if(visited[vertex] == 1)
            continue;
        TopSort(vertex, AdjacencyList, Stack, visited);
    }

    bool answer = true;
    reverse(Stack.begin(), Stack.end());

    for(int i = 0; i < Stack.size() - 1; ++i)
    {
        if (check[pair<int, int>(Stack[i], Stack[i + 1])] != true)
        {
            answer = false;
            break;
        }
    }
    if(answer)
        fout << "YES";
    else
        fout << "NO";

    fin.close();
    fout.close();

    return 0;
}
