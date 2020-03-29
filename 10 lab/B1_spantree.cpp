#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Vertex
{
    double x;
    double y;

    Vertex(double x_, double y_) : x(x_), y(y_) {}
    Vertex() {}

    double distance(const Vertex& point) const
    {
        return pow(x - point.x, 2) + pow(y - point.y, 2);
    }

};

int main()
{
    double sum = 0;

    ifstream fin ("spantree.in");
    ofstream fout("spantree.out");

    int numV;
    fin >> numV;
    int col1, col2;

    vector<double> minE(numV, 1000000000);
    vector<bool> used(numV);
    vector<int> end_edge(numV, -1);
    vector<Vertex> vertices;

    for(int i = 0; i < numV; ++i)
    {
        fin >> col1 >> col2;
        vertices.push_back(Vertex(col1, col2));
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
            sum += sqrt(vertices[ind].distance(vertices[end_edge[ind]]));

        used[ind] = true;

        for (int j = 0; j < numV; ++j)
        {
            if (!used[j])
            {
                if (j == ind)
                    continue;
                if (vertices[ind].distance(vertices[j]) < minE[j])
                {
                    minE[j] = vertices[ind].distance(vertices[j]);
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
