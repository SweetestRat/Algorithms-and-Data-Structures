#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void bfs(vector<vector<char>> &Array, vector<vector<int>> &Way, int &CurX, int &CurY, int &FinishX, int &FinishY, int &CurCycle, int &line, int &symbol, queue<int> &CurrentX, queue<int> &CurrentY, int &done)
{
    if(CurX > 0 && Array[CurX - 1][CurY] != '#' && Way[CurX - 1][CurY] == 0)
    {
        Way[CurX - 1][CurY] = Way[CurX][CurY] + 1;
        CurrentX.push(CurX - 1);
        CurrentY.push(CurY);

        if(CurX - 1 == FinishX && CurY == FinishY)
        {
            done = 1;
            return;
        }
    }

    if(CurX < line - 1 && Array[CurX + 1][CurY] != '#' && Way[CurX + 1][CurY] == 0)
    {
        Way[CurX + 1][CurY] = Way[CurX][CurY] + 1;
        CurrentX.push(CurX + 1);
        CurrentY.push(CurY);

        if(CurX + 1 == FinishX && CurY == FinishY)
        {
            done = 1;
            return;
        }
    }

    if(CurY > 0 && Array[CurX][CurY - 1] != '#' && Way[CurX][CurY - 1] == 0)
    {
        Way[CurX][CurY - 1] = Way[CurX][CurY] + 1;
        CurrentX.push(CurX);
        CurrentY.push(CurY - 1);

        if(CurX == FinishX && CurY - 1 == FinishY)
        {
            done = 1;
            return;
        }
    }

    if(CurY < symbol - 1 && Array[CurX][CurY + 1] != '#' && Way[CurX][CurY + 1] == 0)
    {
        Way[CurX][CurY + 1] = Way[CurX][CurY] + 1;
        CurrentX.push(CurX);
        CurrentY.push(CurY + 1);

        if(CurX == FinishX && CurY + 1 == FinishY)
        {
            done = 1;
            return;
        }
    }
}

int main()
{
    int line, symbol;

    ifstream fin ("input.txt");
    ofstream fout ("output.txt");

    fin >> line >> symbol;

    char matrixCurEl;
    int StartX, StartY, FinishX, FinishY;

    vector<vector<char>> Array(line, vector<char>(symbol, 0));
    vector<vector<int>> Way (line, vector<int> (symbol,0 ));

    for(int i = 0; i < line; ++i)
    {
        for(int j = 0; j < symbol; ++j)
        {
            fin >> matrixCurEl;

            Array[i][j] = matrixCurEl;

            if(matrixCurEl == '#')
                Way[i][j] = -1;

            if(matrixCurEl == 'S')
            {
                StartX = i;
                StartY = j;
            }

            if(matrixCurEl == 'T')
            {
                FinishX = i;
                FinishY = j;
            }
        }
    }

    Way[StartX][StartY] = 1;

    queue<int> CurrentX;
    queue<int> CurrentY;

    CurrentX.push(StartX);
    CurrentY.push(StartY);

    int done = 0;

    while(CurrentX.size() > 0)
    {
        bfs(Array, Way, CurrentX.front(), CurrentY.front(), FinishX, FinishY, Way[CurrentX.front()][CurrentY.front()], line, symbol,
            CurrentX, CurrentY, done);
        CurrentX.pop();
        CurrentY.pop();

        if(done == 1)
            break;
    }

    if(done == 0)
    {
        fout << "-1";
        fin.close();
        fout.close();
        return 0;
    }

    fout << Way[FinishX][FinishY] - 1 << endl;

    string CWay = "";

    while(Way[FinishX][FinishY] != 1)
    {
        if(FinishX != 0 && Way[FinishX][FinishY] - 1 == Way[FinishX - 1][FinishY])
        {
            CWay += "D";
            FinishX -= 1;
        }

        if(FinishX < line - 1 && Way[FinishX][FinishY] - 1 == Way[FinishX + 1][FinishY])
        {
            CWay += "U";
            FinishX += 1;
        }

        if(FinishY != 0 && Way[FinishX][FinishY] - 1 == Way[FinishX][FinishY - 1])
        {
            CWay += "R";
            FinishY -= 1;
        }

        if(FinishY < symbol - 1 && Way[FinishX][FinishY] - 1 == Way[FinishX][FinishY + 1])
        {
            CWay += "L";
            FinishY += 1;
        }
    }

    for(int k = CWay.size() - 1; k >= 0; --k)
    {
        fout << CWay[k];
    }

    fin.close();
    fout.close();

    return 0;
}