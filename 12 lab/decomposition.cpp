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

int dfs2(int vertex, vector<vector<int>> &EdgeIndex, vector<graph> &edges, int flow, int numV, vector<int> &dist, vector<vector<int>> &decompFlow)
{
    if (vertex == numV)
    {
        decompFlow.push_back(vector<int>());
        return flow;
    }
    for (int i = 0; i < EdgeIndex[vertex].size(); ++i)
    {
        if(edges[EdgeIndex[vertex][i]].currentEdgeFlow > 0)
        {
            int result = dfs2(edges[EdgeIndex[vertex][i]].to, EdgeIndex, edges,min(flow,edges[EdgeIndex[vertex][i]].currentEdgeFlow), numV, dist, decompFlow);

            if(result > 0)
            {
               edges[EdgeIndex[vertex][i]].currentEdgeFlow -= result; // - - дает + ))))))))))))) прЕколЛЮхА

               decompFlow.back().push_back(edges[EdgeIndex[vertex][i]].numberE);

               if(vertex == 1)
               {
                   decompFlow.back().push_back(decompFlow.back().size());
                   decompFlow.back().push_back(result); // ОПЯТЬ МИНУС НА МИНУС

                   reverse(decompFlow.back().begin(), decompFlow.back().end());
               }
                return result;
            }
        }
    }
    return 0;
}

int main()
{
    ifstream fin ("decomposition.in");
    ofstream fout ("decomposition.out");

    int numV, numE, from, to, cap;
    int maxflow = INF;
//    int flow = INF;
    int ansFlow = 0;
    fin >> numV >> numE;

    vector<vector<int>> EdgeIndex( numV + 1);
    vector<vector<graph>> g(numV + 1);
    vector<graph> edges;
    vector<int> dist(numV + 1, 0);
    vector<vector<int>> decompFlow;

    for(int i = 0; i < numE; ++i)
    {
        fin >> from >> to >> cap;

        EdgeIndex[from].push_back(edges.size());
        edges.push_back({to, cap, i + 1, 0});
        EdgeIndex[to].push_back(edges.size());
        edges.push_back({from, 0, i + 1, 0});
    }

    vector<int> current(numV + 1, 0);

    while(bfs(1, dist, EdgeIndex, edges, numV))
    {
        while(dfs(1, EdgeIndex, edges, maxflow, numV, dist, current))
        {}
        dist.assign(dist.size(), 0);
        current.assign(current.size(), 0);
    }

    while(dfs2(1, EdgeIndex, edges, INT_MAX, numV, dist, decompFlow))
    {}

    fout << decompFlow.size() << '\n';

    for(int i = 0; i < decompFlow.size(); ++i)
    {
        for(int j = 0; j < decompFlow[i].size(); ++j)
        {
            fout << decompFlow[i][j] << ' ';
        }

        fout << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
