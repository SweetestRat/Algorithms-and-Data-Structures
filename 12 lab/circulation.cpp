#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF INT_MAX

using namespace std;

struct graph
{
    int to;
    int capacity;
    int numberE;
    int currentEdgeFlow;
};

bool bfs(int s, vector<int> &dist, vector<vector<int>> &EdgeIndex, vector<graph> &edges, int numV)
{
    queue<int> q;
    q.push(s);

    dist[s] = 1;

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        for(int i = 0; i < EdgeIndex[v].size(); ++i)
        {
            int to = edges[EdgeIndex[v][i]].to;

            if(dist[to] == 0 && edges[EdgeIndex[v][i]].capacity - edges[EdgeIndex[v][i]].currentEdgeFlow > 0)
            {
                q.push(to);
                dist[to] = dist[v] + 1;
            }
        }
    }
    return dist[numV] != 0;
}

int dfs(int vertex, vector<vector<int>> &EdgeIndex, vector<graph> &edges, int maxflow, int numV, vector<int> &dist, vector<int> &current)
{
    if (vertex == numV || maxflow == 0)
        return maxflow;

    for ( ; current[vertex] < EdgeIndex[vertex].size(); ++current[vertex]) // пока кол-во смежных > кол-во пройденных
    {
        if(dist[vertex] + 1 != dist[edges[EdgeIndex[vertex][current[vertex]]].to])
            continue;

        int result = dfs(edges[EdgeIndex[vertex][current[vertex]]].to, EdgeIndex, edges, min(maxflow, edges[EdgeIndex[vertex][current[vertex]]].capacity - edges[EdgeIndex[vertex][current[vertex]]].currentEdgeFlow), numV, dist, current);

        if (result != 0)
        {
            edges[EdgeIndex[vertex][current[vertex]]].currentEdgeFlow += result;

            edges[EdgeIndex[vertex][current[vertex]]^1].currentEdgeFlow -= result;

            return result;
        }
    }
    return 0;
}

int main()
{
    ifstream fin ("circulation.in");
    ofstream fout ("circulation.out");

    int numV, numE, from, to, minCap, maxCap, numEdge;
    int maxflow = INF;
    fin >> numV >> numE;

    vector<vector<int>> EdgeIndex( numV + 3);
    vector<graph> edges;
    vector<int> dist(numV + 3, 0);
    vector<int> ans;

    for(int i = 0; i < numE; ++i)
    {
        fin >> from >> to >> minCap >> maxCap;

        EdgeIndex[from].push_back(edges.size());
        edges.push_back({to, maxCap - minCap, i + 1, 0});

        EdgeIndex[to].push_back(edges.size());
        edges.push_back({from, 0, i + 1, 0});

        numEdge = edges.size() - 2;
        EdgeIndex[numV + 1].push_back(edges.size());
        edges.push_back({to, minCap, numEdge, 0});

        EdgeIndex[to].push_back(edges.size());
        edges.push_back({numV + 1, 0, numEdge, 0});

        EdgeIndex[from].push_back(edges.size());
        edges.push_back({numV + 2, minCap, i + 1, 0});

        EdgeIndex[numV + 2].push_back(edges.size());
        edges.push_back({from, 0, i + 1, 0});
    }

    vector<int> current(numV + 3, 0);

    while(bfs(numV + 1, dist, EdgeIndex, edges, numV + 2))
    {
        while(dfs(numV + 1, EdgeIndex, edges, maxflow, numV + 2, dist, current))
        {}
        dist.assign(dist.size(), 0);
        current.assign(current.size(), 0);
    }

    for(int i = 0; i < EdgeIndex[numV + 1].size(); ++i)
    {
        if(edges[EdgeIndex[numV + 1][i]].capacity == edges[EdgeIndex[numV + 1][i]].currentEdgeFlow)
            ans.push_back(edges[EdgeIndex[numV + 1][i]].capacity + edges[edges[EdgeIndex[numV + 1][i]].numberE].currentEdgeFlow);
        else
        {
            fout << "NO";
            return 0;
        }
    }

    fout << "YES\n";

    for(int i = 0; i < ans.size(); ++i)
    {
        fout << ans[i] << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
