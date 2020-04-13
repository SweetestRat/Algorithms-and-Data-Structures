#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 100000000001;

struct edge
{
    int from, to, weight;
};

int main()
{

    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    int numV, w;
    fin >> numV;

    vector<long long> dist(numV, inf);
    vector<long long> parent(numV, -1);
    vector<edge> g;

    for(int i = 0; i < numV; ++i)
    {
        for(int j = 0; j < numV; ++j)
        {
            fin >> w;
            if(w != 1000000000)
                g.push_back({i, j, w});
        }
    }

    int x;

    for (int i = 0; i < numV; ++i)
    {
        x = -1;
        for (int j = 0; j < g.size(); ++j)
        {
            if (dist[g[j].to] > dist[g[j].from] + g[j].weight)
            {
                dist[g[j].to] = max(-inf, dist[g[j].from] + g[j].weight);
                parent[g[j].to] = g[j].from;
                x = g[j].to;
            }
        }
    }


    if(x == -1)
        fout << "NO";
    else {
        int y = x;

        for(int i = 0; i < numV; ++i)
            y = parent[y];

        vector<long long> ans;

        for(int cur = y; ; cur = parent[cur])
        {
            ans.push_back(cur);

            if(cur == y && ans.size() > 1)
                break;
        }

         reverse(ans.begin(), ans.end());
         fout << "YES\n" << ans.size() << endl;
         for(int i = 0; i < ans.size(); ++i)
             fout << ans[i] + 1 << ' ';
    }
    return 0;
}
