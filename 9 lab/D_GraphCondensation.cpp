#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("cond.in");
ofstream fout ("cond.out");

vector<vector<int>> RealAdjList;
vector<vector<int>> ReverseAdjList;
vector<char> visited;
vector<int> order, component;
int componentPointer = 0;

void dfs1(int vertex)
{
    visited[vertex] = 1;

    for(int i = 0; i < RealAdjList[vertex].size(); ++i)
    {
        if(visited[RealAdjList[vertex][i]] == 0)
            dfs1(RealAdjList[vertex][i]);
    }

    order.push_back(vertex);
}

void dfs2(int vertex)
{
    visited[vertex] = 1;
    component[vertex] = componentPointer;

    for(int i = 0; i < ReverseAdjList[vertex].size(); ++i)
    {
        if(visited[ReverseAdjList[vertex][i]] == 0)
        {
            dfs2(ReverseAdjList[vertex][i]);
        }
    }
}

int main()
{
    int col1, col2;
    int numV, numE;

    fin >> numV >> numE;
    if(numE == 0)
    {
        fout << numV << endl;
        for(int i = 1; i <= numV; ++i)
            fout << i << ' ';
        return 0;
    }

    RealAdjList.assign(numV + 1, vector<int>());
    ReverseAdjList.assign(numV + 1, vector<int>());
    component.assign(numV + 1, 0);

    for(int edge = 0; edge < numE; ++edge)
    {
        fin >> col1 >> col2;
        if(col1 != col2)
        {
            RealAdjList[col1].push_back(col2);
            ReverseAdjList[col2].push_back(col1);
        }
    }

    visited.assign(numV + 1, 0);
    for(int i = 1; i <= numV; ++i)
    {
        if(visited[i] == 0)
            dfs1(i);
    }

    visited.assign(numV + 1, 0);
    for(int i = order.size() - 1; i > 0; --i)
    {
        if(visited[order[i]] == 0)
        {
            componentPointer += 1;
            dfs2(order[i]);
        }
    }

    fout << componentPointer << endl;

    for(int i = 1; i <= numV; ++i)
    {
        fout << component[i] << ' ';
    }
    return 0;
}
