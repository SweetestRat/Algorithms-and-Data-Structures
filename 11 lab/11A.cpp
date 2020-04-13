#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    const long long inf = 100000000001;

    ifstream fin ("pathmgep.in");
    ofstream fout ("pathmgep.out");

    long long numV, S, F;
    long long weight;
    long long v;

    fin >> numV >> S >> F;
    vector<vector<pair<long long, long long>>> g(numV, vector<pair<long long , long long>>());
    vector<long long> dist (numV, inf);
    set<pair<long long, long long>> SetCur;

    for(int i = 0; i < numV; ++i)
    {
        for(int j = 0; j < numV; ++j)
        {
            fin >> weight;

            if(weight > 0)
            {
                g[i].push_back(make_pair(j, weight));
            }
        }
    }

    dist[S - 1] = 0;

    SetCur.insert({0, S - 1});

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

    if(dist[F - 1] != inf)
        fout << dist[F - 1];
    else
        fout << "-1";

    fin.close();
    fout.close();
    return 0;
}