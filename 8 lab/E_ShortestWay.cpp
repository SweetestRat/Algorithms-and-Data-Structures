#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int numofgraphVertex, numofgraphEdges;
    queue<int> Queue;

    ifstream fin ("pathbge1.in");
    ofstream fout ("pathbge1.out");

    fin >> numofgraphVertex >> numofgraphEdges;
    vector<vector<int>> AdjacencyList(numofgraphVertex, vector<int>());
    int mindistance[numofgraphVertex];

    for(int md = 0; md < numofgraphVertex; ++md)
    {
        mindistance[md] = 0;
    }

    int col1, col2;

    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1 - 1].push_back(col2);
        AdjacencyList[col2 - 1].push_back(col1);
    }

    int nodes[numofgraphVertex];

    for(int nds = 0; nds < numofgraphVertex; ++nds)
    {
        nodes[nds] = 0;
    }

    for(int l = 0; l < AdjacencyList[0].size(); ++l)
    {
        nodes[0] = 2;
        Queue.push(AdjacencyList[0][l]);
        mindistance[AdjacencyList[0][l] - 1] += 1;
        nodes[AdjacencyList[0][l] - 1] = 1;
    }

        while (!Queue.empty())
        {
            int curNode = Queue.front();
            Queue.pop();

            nodes[curNode - 1] = 2;

            for (int vertex = 0; vertex < AdjacencyList[curNode - 1].size(); ++vertex)
            {
                if (nodes[AdjacencyList[curNode - 1][vertex] - 1] == 0)
                {
                    nodes[AdjacencyList[curNode - 1][vertex] - 1] = 1;
                    Queue.push(AdjacencyList[curNode - 1][vertex]);
                    mindistance[AdjacencyList[curNode - 1][vertex] - 1] = mindistance[curNode - 1] + 1;
                }
            }
        }

    for (int i = 0; i < numofgraphVertex; ++i)
    {
        fout << mindistance[i] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
