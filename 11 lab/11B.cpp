#include <fstream>

using namespace std;

int main()
{
    const int inf = INT_MAX;

    ifstream fin ("pathsg.in");
    ofstream fout ("pathsg.out");

    int col1, col2, numV, numE, S;
    int weight;
    int v;

    fin >> numV >> numE;

    int dist[numV][numV];

    for(int i = 0; i < numV; ++i)
    {
        for(int j = 0; j < numV; ++j)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = inf;
        }
    }

    for(int i = 0; i < numE; ++i)
    {
        fin >> col1 >> col2 >> weight;
        dist[col1 - 1][col2 - 1] = weight;
    }

    for(int k = 0; k < numV; ++k)
        for(int i = 0; i < numV; ++i)
            for(int j = 0; j < numV; ++j)
                if(dist[i][k] < inf && dist[k][j] < inf)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

                for(int i = 0; i < numV; ++i)
                {
                    for (int j = 0; j < numV; ++j)
                    {
                        fout << dist[i][j] << ' ';
                    }
                    fout << endl;
                }

    fin.close();
    fout.close();
    return 0;
}