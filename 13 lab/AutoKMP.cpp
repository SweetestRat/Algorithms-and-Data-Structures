#include <iostream>
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
    int alphabetSize;
    string s;
    cin >> alphabetSize;
    cin >> s;
    int stringSize = s.size();
    vector<int> pi(stringSize, 0);
    vector<vector<int>> ans (stringSize + 1, vector<int> (alphabetSize, 0));
    createLPSArray(s, s.size(), pi);

    for(auto i = 0; i <= stringSize; ++i)
    {
        for(char l = 97; l < alphabetSize + 97; ++l)
        {
            if(i == stringSize)
                ans[i][l - 97] = ans[pi[i - 1]][l - 97];
            if(i > 0 && l != s[i])
                ans[i][l - 97] = ans[pi[i - 1]][l - 97];
            else if(l == s[i])
                ans[i][l - 97] = i + 1;
            else if(l != s[i])
                ans[i][l - 97] = i;
        }
    }

    for(auto i = 0; i <= stringSize; ++i)
    {
        for(auto l = 0; l < alphabetSize; ++l)
        {
            cout << ans[i][l] << ' ';
        }
        cout << '\n';
    }

    return 0;
}