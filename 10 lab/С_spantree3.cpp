#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int dsu_get(int vertex, vector<int> &color)
{
    if (vertex == color[vertex])
        return vertex;
    else
        return (color[vertex] = dsu_get(color[vertex], color));
}

void dsu_unite(int v1, int v2, vector<int> &color)
{
     v1 = dsu_get(v1, color);
     v2 = dsu_get(v2, color);

     if(v1 != v2)
         color[v1] = v2;
}

int main()
{
    long long int sum = 0;

    ifstream fin ("spantree3.in");
    ofstream fout("spantree3.out");

    vector<pair<int, pair<int, int>>> graph; // weight, vertex 1, vertex 2

    int numV, numE, vertex1, vertex2, weight;
    fin >> numV >> numE;
    vector<int> color(numV);

    pair<int, pair<int, int>> el;

    for(int i = 0; i < numE; ++i)
    {
        fin >> vertex1 >> vertex2 >> weight;
        el.first = weight;
        el.second = pair<int, int>(vertex1 - 1, vertex2 - 1);

        graph.push_back(el);
    }

    sort(graph.begin(), graph.end());

    for(int i = 0; i < numV; ++i)
        color[i] = i;

    for(int i = 0; i < numE; ++i)
    {
        int v1 = graph[i].second.first, v2 = graph[i].second.second, w = graph[i].first;
        if (dsu_get(v1, color) != dsu_get(v2, color))
        {
            sum += graph[i].first;
            dsu_unite(v1, v2, color);
        }
    }

    fout << sum;

    fin.close();
    fout.close();
    return 0;
}
