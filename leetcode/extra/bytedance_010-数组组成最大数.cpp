#include <bits/stdc++.h>
using namespace std;

int main() {
    string buf;
    cin >> buf;
    int n = buf.size();
    buf.back() = ',';
    vector<string> vec;
    for(int i = 1, j; i < n; ++i) {
        for(j = i; i < n && buf[i] != ','; ++i);
        vec.push_back(buf.substr(j, i - j));
    }
    sort(vec.begin(), vec.end(), [&](string const &u, string const &v) {
        return u + v > v + u;
    });
    buf = "";
    for(auto &it: vec)
        buf += it;
    cout << buf << endl;
}
