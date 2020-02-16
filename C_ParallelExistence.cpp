#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int graphVertex, graphEdges, pointer = 0;
    bool noparallel = true;

    ifstream fin ("input.txt");
    ofstream fout("output.txt");

    fin >> graphVertex >> graphEdges;

    int col1[graphEdges], col2[graphEdges];

    for(int i = 0; i < graphEdges; ++i)
    {
        fin >> col1[i] >> col2[i];
    }

    int i = 0;

    while(noparallel)
    {
        for(int j = i+1; j < graphEdges; ++j)
        {
            if((col1[i] == col2[j] && col2[i] == col1[j]) || (col1[i] == col1[j] && col2[i] == col2[j]))
            {
                pointer++;
                noparallel = false;
            }
        }
        i++;
        if(i == graphEdges)
            break;
    }

    if(pointer == 0)
        fout << "NO";
    else
        fout << "YES";

    fin.close();
    fout.close();

    return 0;
}

