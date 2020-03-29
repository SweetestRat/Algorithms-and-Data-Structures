#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
    double sum = 0;

    ifstream fin ("spantree.in");
    ofstream fout("spantree.out");

    int numV;
    fin >> numV;
    int col1[numV], col2[numV];

    vector<double> minE(numV, 1000000000);
    double graph[numV][numV];
    vector<bool> used(numV);
    vector<int> end_edge(numV, -1);

    for(int i = 0; i < numV; ++i)
    {
        fin >> col1[i] >> col2[i];
    }

    for(int i = 0; i < numV; ++i)
    {
        for(int j = 0; j < numV; ++j)
        {
            graph[i][j] = pow((col1[j] - col1[i]), 2) + pow((col2[j] - col2[i]), 2);
            graph[j][i] = graph[i][j];
        }
    }

    minE[0] = 0;

    for(int v = 0; v < numV; ++v)
    {
        int ind = -1;

        for(int i = 0; i < numV; ++i)
        {
            if ((!used[i]) && (ind == -1 || minE[i] < minE[ind]))
                ind = i;
        }

        if (end_edge[ind] != -1)
            sum += sqrt(graph[ind][end_edge[ind]]);

        used[ind] = true;

        for (int j = 0; j < numV; ++j)
        {
            if (!used[j])
            {
                if (j == ind)
                    continue;
                if (graph[ind][j] < minE[j])
                {
                    minE[j] = graph[ind][j];
                    end_edge[j] = ind;
                }
            }
        }
    }

    fout << setprecision(10) << sum;

    fin.close();
    fout.close();
    return 0;
}