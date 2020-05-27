#include <fstream>
#include <vector>

using namespace std;

void createLPSArray(string pat, int size, vector<int> &lps)
{
    int j = 0;
    int i = 1;
    lps[0] = 0;

    while(i < size)
    {
        if (pat[j] == pat[i])
        {
            lps[i] = j + 1;
            i++;
            j++;
        } else if(pat[j] != pat[i])
        {
            if(j != 0)
                j = lps[j - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main()
{
    ifstream fin ("prefix.in");
    ofstream fout("prefix.out");

    string s;
    fin >> s;
    vector<int> lps(s.size(), 0);

    createLPSArray(s, s.size(), lps);

    for(int i = 0; i < lps.size(); ++i)
    {
        fout << lps[i] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
