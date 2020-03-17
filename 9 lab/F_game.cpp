#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Way
{
public:
    int vertex;
    int distance;

    Way() {}
    Way(int _vertex, int _distance) : vertex(_vertex), distance(_distance) {}
};

bool compare(Way& l, Way& r)
{
    if (l.distance < r.distance)
        return true;
    return false;
}

int BFS(vector<vector<int>> &graph, vector<Way> &ways, int startVertex)
{
    queue<int> _queue;
    vector<bool> used(graph.size());
    vector<int> distance(graph.size());

    _queue.push(startVertex);

    while (_queue.size() > 0)
    {
        int vertex = _queue.front();
        _queue.pop();

        used[vertex] = true;

        for (int i = 0; i < graph[vertex].size(); i++)
        {
            int toVertex = graph[vertex][i];

            if (used[toVertex] == false)
            {
                distance[toVertex] = distance[vertex] + 1;

                if (graph[toVertex].size() == 0)
                {
                    ways.push_back(Way(toVertex, distance[toVertex]));
                }

                _queue.push(toVertex);
            }
        }
    }

    auto it = min_element(ways.begin(), ways.end(), compare);

    return it->distance;
}

int main()
{
    vector<Way> ways;


    int numofgraphVertex, numofgraphEdges, startVertex;
    queue<int> Queue;

    ifstream fin ("game.in");
    ofstream fout ("game.out");

    fin >> numofgraphVertex >> numofgraphEdges >> startVertex;
    vector<vector<int>> AdjacencyList(numofgraphVertex + 1, vector<int>());

    int col1, col2;

    for(int i = 0; i < numofgraphEdges; ++i)
    {
        fin >> col1 >> col2;
        AdjacencyList[col1].push_back(col2);
    }

    if(AdjacencyList[startVertex].empty())
    {
        fout << "Second player wins";
        return 0;
    }

    if (BFS(AdjacencyList, ways, startVertex) % 2 != 0)
    {
        fout << "First player wins";
    }
    else
    {
        fout << "Second player wins";
    }

    fin.close();
    fout.close();
    return 0;
}