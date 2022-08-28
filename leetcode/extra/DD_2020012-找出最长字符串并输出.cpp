#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
        int n = s.size();
        string t = "#";
        for(int i = 0; i < n; ++i) {
            t.push_back(s[i]);
            t.push_back('#');
        }
        int m = n + n + 1;
        vector<int> h(m);
        for(int i = 0, p = -1, d = 0; i < m; ++i) {
            h[i] = i < p + d ? min(h[p + p - i], p + d - i) : 1;
            for( ; i - h[i] >= 0 && i + h[i] < m && t[i - h[i]] == t[i + h[i]]; ++h[i]);
            if(i + h[i] > p + d) {
                p = i;
                d = h[i];
            }
        }
        int p = max_element(h.begin(), h.end()) - h.begin();
        s = t.substr(p - h[p] + 1, h[p] + h[p] - 1);
        t = "";
        for(char ch: s)
            if(ch != '#')
                t.push_back(ch);
    cout << t << endl;
    return 0;
}
