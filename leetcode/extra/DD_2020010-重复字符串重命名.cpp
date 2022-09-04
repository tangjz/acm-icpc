#include <bits/stdc++.h>
using namespace std;

vector<string_view> split(string_view s, char sep = '.') {
    int n = s.size();
    vector<string_view> ret;
    for(int i = 0; i < n; ++i) {
        int j = i;
        for( ; i < n && s[i] != sep; ++i);
        ret.push_back(s.substr(j, i - j));
    }
    if(!s.empty() && s.back() == sep)
        ret.push_back(s.substr(s.size()));
    return move(ret);
}

int main() {
    string buf;
    cin >> buf;
    vector<string_view> seq = split(buf, ',');
    unordered_map<string_view, int> ctr;
    string out = "";
    bool fir = 1;
    for(auto &item: seq) {
        if(fir) {
            fir = 0;
        } else {
            out += "', '";
        }
        int cnt = ++ctr[item];
        out += (string)item;
        if(cnt > 1) {
            out += "_" + to_string(cnt - 2);
        }
    }
    cout << "['" + out + "']" << endl;
    return 0;
}
