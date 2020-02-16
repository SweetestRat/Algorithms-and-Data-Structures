#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int numofvertices;
    int numofarcs;

    fin >> numofvertices;
    fin >> numofarcs;

    int matrix[numofvertices][numofvertices];

    for(int i = 0; i < numofvertices; ++i)
    {
        for(int j = 0; j < numofvertices; ++j)
        {
            matrix[i][j] = 0;
        }
    }

    int x, y;

    for(int i = 0; i < numofarcs ; ++i)
    {
        fin >> x >> y;
        matrix[x - 1][y - 1] = 1;
    }

    for(int i = 0; i < numofvertices; ++i)
    {
        for(int j = 0; j < numofvertices; ++j)
        {
            fout << matrix[i][j] << ' ';
        }
        fout << endl;
    }

    return 0;
}
