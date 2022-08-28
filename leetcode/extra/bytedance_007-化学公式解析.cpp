#include <bits/stdc++.h>
using namespace std;

class Solution {
    typedef map<string, int> Atoms;
    Atoms parseFormula(int &pos, string &formula) {
        Atoms ret;
        while(pos < (int)formula.length())
            if(formula[pos] == '(') {
                Atoms tmp = parseFormula(++pos, formula);
                assert(formula[pos] == ')');
                int sta = ++pos;
                while(pos < (int)formula.length() && isdigit(formula[pos]))
                    ++pos;
                int val = sta < pos ? stoi(formula.substr(sta, pos - sta)) : 1;
                for(auto &it : tmp)
                    ret[it.first] += val * it.second;
            } else if(formula[pos] == ')') {
                break;
            } else if(isupper(formula[pos])) {
                int sta = pos++;
                while(pos < (int)formula.length() && islower(formula[pos]))
                    ++pos;
                string name = formula.substr(sta, pos - sta);
                sta = pos;
                while(pos < (int)formula.length() && isdigit(formula[pos]))
                    ++pos;
                int val = sta < pos ? stoi(formula.substr(sta, pos - sta)) : 1;
                ret[name] += val;
            }
        return ret;
    }
public:
    string countOfAtoms(string formula) {
        int pos = 0;
        Atoms ret = parseFormula(pos, formula);
        string ans;
        for(auto &it : ret) {
            ans += it.first;
            ans += to_string(it.second);
        }
        return ans;
    }
} obj;

int main() {
    string s;
    cin >> s;
    for(char &ch: s)
        if(ch == '[') {
            ch = '(';
        } else if(ch == ']') {
            ch = ')';
        }
    cout << obj.countOfAtoms(s) << endl;
}
