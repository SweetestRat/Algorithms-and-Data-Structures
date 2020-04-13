#include <iostream>
#include <fstream>
#include <vector>
#include<set>

using namespace std;

int main()
{
    const long long inf = INT_MAX;

    ifstream fin ("pathbgep.in");
    ofstream fout ("pathbgep.out");

    int numV, numE;
    int col1, col2, weight;
    int v;

    fin >> numV >> numE;
    vector<vector<pair<long long, long long>>> g(numV, vector<pair<long long , long long>>());
    vector<long long> dist (numV, inf);
    set<pair<int, int>> SetCur;

    for(int i = 0; i < numE; ++i)
    {
        fin >> col1 >> col2 >> weight;

        g[col1 - 1].push_back(make_pair(col2 - 1, weight));
        g[col2 - 1].push_back(make_pair(col1 - 1, weight));
    }

    dist[0] = 0;

    SetCur.insert({0, 0});

    while(!SetCur.empty())
    {
        v = SetCur.begin()->second;
        SetCur.erase(SetCur.begin());

        for (int y = 0; y < g[v].size(); ++y)
        {
            if (dist[g[v][y].first] > dist[v] + g[v][y].second)
            {
                SetCur.erase({dist[g[v][y].first], g[v][y].first});
                dist[g[v][y].first] = dist[v] + g[v][y].second;
                SetCur.insert({dist[g[v][y].first], g[v][y].first});
            }
        }
    }

    for(int i = 0; i < numV; ++i)
    {
        fout << dist[i] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
