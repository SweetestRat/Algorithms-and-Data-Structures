#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin ("input.txt");
    ofstream fout("output.txt");

    int numofgraphVertex, numofgraphEdges;

    fin >> numofgraphVertex >> numofgraphEdges;

    int vertexDegree[numofgraphVertex];
    int col1[numofgraphEdges], col2[numofgraphEdges];

    for(int i = 0; i < numofgraphVertex; ++i)
    {
        vertexDegree[i] = 0;
    }

    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1[i] >> col2[i];
    }

    for(int i = 1; i <= numofgraphVertex; ++i)
    {
        for(int j = 0; j < numofgraphEdges; ++j)
        {
            if(col1[j] == i || col2[j] == i)
            {
                vertexDegree[i - 1] += 1;
            }
        }
    }

    for(int i = 0; i < numofgraphVertex; ++i)
    {
        fout << vertexDegree[i] << ' ';
    }

    fin.close();
    fout.close();

    return 0;
}
