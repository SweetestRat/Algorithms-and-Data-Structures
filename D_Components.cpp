#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

void dfs(int vertex, vector<int> &Colour, vector<vector<int>> &AdjacencyList, int componentsPointer)
{

    Colour[vertex] = componentsPointer;

    for(int i = 0; i < AdjacencyList[vertex].size(); ++i)
    {
        if(Colour[AdjacencyList[vertex][i]] == 0)
        {
            dfs(AdjacencyList[vertex][i], Colour, AdjacencyList, componentsPointer);
        }
    }
}

int main()
{
    int numofgraphVertex, numofgraphEdges;
    int componentsPointer = 0;

    ifstream fin("components.in");
    ofstream fout("components.out");

    fin >> numofgraphVertex >> numofgraphEdges;

    vector<vector<int>> AdjacencyList(numofgraphVertex + 1, vector<int>());

    vector<int> Colour (numofgraphVertex + 1, 0);

    int col1, col2;

    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);
        AdjacencyList[col2].push_back(col1);
    }

    for(int vertex = 1; vertex <= numofgraphVertex; ++vertex)
    {
        if (Colour[vertex] == 0)
        {
            Colour[vertex] = 1;
            componentsPointer += 1;
            dfs(vertex, Colour, AdjacencyList, componentsPointer);
        }
    }

    fout << componentsPointer << endl;

    for(int k = 1; k <= numofgraphVertex; ++k)
    {
        fout << Colour[k] << ' ';
    }

    fout << endl;

    fin.close();
    fout.close();
}
