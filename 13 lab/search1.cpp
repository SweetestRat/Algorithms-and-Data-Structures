#include <fstream>
#include <vector>

using namespace std;

vector<int> ans;

void findMatches(string p, string t)
{
    auto m = p.size() - 1;
    auto n = t.size();

    for(auto i = 0, j = 0; i < n; ++i)
    {
        while(t[i] == p[j])
        {
            if (j == m)
            {
                ans.push_back(i - m + 1);
                j = 0;
                i = i - m;
                break;
            }

            i++;
            j++;
        }
        j = 0;
    }
}

int main()
{
    ifstream fin ("search1.in");
    ofstream fout("search1.out");

    string p, t;
    fin >> p >> t;

    findMatches(p, t);

    fout << ans.size() << '\n';

    for(int an : ans)
    {
        fout << an << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
