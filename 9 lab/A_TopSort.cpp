#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

ifstream fin ("topsort.in");
ofstream fout ("topsort.out");

void dfs(int vertex, vector<int> &visited, vector<vector<int>> &AdjacencyList, bool &cycle)
{

    visited[vertex] = 1;

    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(visited[AdjacencyList[vertex][i]] == 0)
        {
            dfs(AdjacencyList[vertex][i], visited, AdjacencyList, cycle);
        } else
            cycle = true;
    }

    if(cycle)
    {
        fout << "-1";
        exit(0);
    }

    visited[vertex] = 0;
}

void TopSort(int vertex, vector<vector<int>> &AdjacencyList, stack<int> &Stack, vector<int> &visited)
{
    visited[vertex] = 1;

    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(visited[AdjacencyList[vertex][i]] == 1)
            continue;
        TopSort(AdjacencyList[vertex][i], AdjacencyList, Stack, visited);
    }
    Stack.push(vertex);
}

int main() {
    int numofgraphVertex, numofgraphEdges;
    int col1, col2;

    fin >> numofgraphVertex >> numofgraphEdges;
    if(numofgraphEdges == 0)
    {
        fout << "-1";
        return 0;
    }

    vector<vector<int>> AdjacencyList (numofgraphVertex + 1, vector<int>());
    vector<int> visited (numofgraphVertex + 1, 0);
    stack<int> Stack;
    bool cycle = false;

    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);
    }

    for(int vertex = 1; vertex <= numofgraphVertex; ++vertex)
    {
        if (visited[vertex] == 0)
        {
            visited[vertex] = 1;
            dfs(vertex, visited, AdjacencyList, cycle);
        }
    }

    for(int vertex = 1; vertex <= numofgraphVertex; ++vertex)
    {
        if(visited[vertex] == 1)
            continue;

        TopSort(vertex, AdjacencyList, Stack, visited);
    }

    while(!Stack.empty())
    {
        fout << Stack.top() << ' ';
        Stack.pop();
    }

    fin.close();
    fout.close();

    return 0;
}
