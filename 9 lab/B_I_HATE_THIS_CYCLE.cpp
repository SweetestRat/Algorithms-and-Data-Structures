#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("cycle.in");
ofstream fout ("cycle.out");

bool dfs(int vertex, vector<char> &color, vector<int> &parent, int &cycleStart, int &cycleEnd, vector<vector<int>> &AdjacencyList)
{
    color[vertex] = 1;

    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(color[AdjacencyList[vertex][i]] == 0)
        {
            parent[AdjacencyList[vertex][i]] = vertex;
            if(dfs(AdjacencyList[vertex][i], color, parent, cycleStart, cycleEnd, AdjacencyList))
                return true;
        }
        else if(color[AdjacencyList[vertex][i]] == 1)
        {
            cycleEnd = vertex;
            cycleStart = AdjacencyList[vertex][i];
            return true;
        }
    }

    color[vertex] = 2;
    return false;
}

int main()
{
    int col1, col2;
    int numofgraphVertex, numofgraphEdges;
    fin >> numofgraphVertex >> numofgraphEdges;

    vector<vector<int>> AdjacencyList (numofgraphVertex + 1, vector<int>());
    vector<char> color(numofgraphVertex + 1, 0);
    vector<int> parent(numofgraphVertex + 1, -1);
    int cycleStart = -1, cycleEnd = -1;


    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);
    }

    for(int vertex = 1; vertex <= numofgraphVertex; ++vertex)
    {
        if (dfs(vertex, color, parent, cycleStart, cycleEnd, AdjacencyList))
            break;
    }

    if(cycleStart == -1)
        fout << "NO";
    else {
        fout << "YES\n";
        vector<int> way;

        for(int vertex = cycleEnd; vertex != cycleStart; vertex = parent[vertex]) {
            way.push_back(vertex);
        }
        way.push_back(cycleStart);

        for(int i = way.size() - 1; i >= 0; --i)
            fout << way[i] << ' ';
    }

    return 0;
}
