#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const long long inf = 2*1000000000000000010;

struct node
{
    int to;
    long long dist;
    node(int to, long long dist) : to(to), dist(dist) {};
};

void dfs(int v, vector<bool> &used, vector<vector<node>> g)
{
    used[v] = true;

    for(int i = 0; i < g[v].size(); ++i)
    {
        int to = g[v][i].to;
        if(!used[to])
            dfs(to, used, g);
    }
}

void Bellman_Ford(vector<long long> &d, int s, int numV, vector<vector<node>> g,vector<bool> &used)
{

    d[s] = 0;
    queue <int> cycleHelp;

    for(int i = 1; i <= numV; ++i)
        for(int j = 1; j <= numV; ++j)
            for(int k = 0; k < g[j].size(); ++k)
            {
                int to = g[j][k].to;
                long long dist = g[j][k].dist;

                if((d[j] < inf) && (d[to] > d[j] + dist))
                {
                    d[to] = max(-inf, d[j] + dist);

                    if(i == numV)
                    {
                        cycleHelp.push(j);
                    }
                }
            }

    while(!cycleHelp.empty())
    {
        used[cycleHelp.front()] = true;
        dfs(cycleHelp.front(), used, g);
        cycleHelp.pop();
    }
}

int main()
{
    ifstream fin("path.in");
    ofstream fout("path.out");

    int numV, numE, s, first, second;
    long long w;
    fin >> numV >> numE >> s;
    vector<vector<node>> g(numV + 1);
    vector<long long> d(numV + 1, inf);
    vector<bool> used(numV + 1);

    for(int i = 0; i < numE; ++i)
    {
        fin >> first >> second >> w;

        g[first].push_back(node(second, w));
    }

    Bellman_Ford(d, s, numV, g, used);

    for(int i = 1; i <= numV; ++i)
    {
        if(d[i] == inf)
        {
            fout << "*\n";
            continue;
        }
        if(used[i])
        {
            fout << "-\n";
            continue;
        }
        fout << d[i] << endl;
    }

    fin.close();
    fout.close();

    return 0;
}