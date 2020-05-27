#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<size_t> prefix_function (string s)
{
    size_t n =  s.length();
    vector<size_t> pi(n);
    for (size_t i=1; i<n; ++i)
    {
        size_t j = pi[i-1];
        while ((j > 0) && (s[i] != s[j]))
            j = pi[j-1];

        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string str;
    string str2;
    int count = 0;
    vector <size_t> numIn;
    ifstream in("search2.in");
    ofstream out("search2.out");
    in >> str;
    in >> str2;
    size_t k = 0;
    size_t l = 0;
    size_t num;
    vector <size_t> prefix = prefix_function(str);
    for (k = 0; k < str2.size(); k++){
        while (str2[k] == str[l]){
            if (l == (str.size()-1)){
                num = k - l;
                count++;
                num++;
                numIn.push_back(num);
                l = 0;
            }
            else {
                k++;
                l++;
            }
        }
        if (l != 0)
            l = prefix[l - 1];
    }
    out << count << endl;
    for (size_t i = 0; i < numIn.size(); i++){
        out << numIn[i] << " ";
    }
    return 0;
}