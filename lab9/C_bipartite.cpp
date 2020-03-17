#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("bipartite.in");
ofstream fout ("bipartite.out");

void dfs(int vertex, vector<vector<int>> &AdjacencyList, vector<int> &color)
{
    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(color[AdjacencyList[vertex][i]] == 0)
        {
            if(color[vertex] == 1)
            {
                color[AdjacencyList[vertex][i]] = 2;
            }
            else if(color[vertex] == 2)
            {
                color[AdjacencyList[vertex][i]] = 1;
            }
            dfs(AdjacencyList[vertex][i], AdjacencyList, color);
        }
        else if(color[vertex] == color[AdjacencyList[vertex][i]])
        {
            fout << "NO\n";
            exit(0);
        }
    }
}

int main() {
    int numofgraphVertex, numofgraphEdges;
    int col1, col2;

    fin >> numofgraphVertex >> numofgraphEdges;

    if(numofgraphVertex == 1)
    {
        fout << "YES";
        return 0;
    }

    vector<vector<int>> AdjacencyList(numofgraphVertex + 1, vector<int>());
    vector<int> color(numofgraphVertex + 1, 0);

    for (int i = 0; i < numofgraphEdges; ++i) {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);
        AdjacencyList[col2].push_back(col1);
    }

    for (int vertex = 1; vertex <= numofgraphVertex; ++vertex) {
        if (color[vertex] == 0) {
            color[vertex] = 1;
            dfs(vertex, AdjacencyList, color);
        }
    }

    fout << "YES";

    return 0;
}