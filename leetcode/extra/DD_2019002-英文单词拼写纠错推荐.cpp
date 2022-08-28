#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const string fir = "qwertasdfgzxcv", sec = "yuiophjklbnm";

int idx[257];

int calc(string const &A, string const &B) {
    int n = A.size(), m = B.size();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;
    for(int i = 0; i <= n; ++i)
        for(int j = 0;j <= m; ++j) {
            if(i > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 3);
            if(j > 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 3);
            if(i > 0 && j > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 0 : (1 + (idx[A[i - 1]] != idx[B[j - 1]]))));
        }
    return dp[n][m];
}

int main() {
    for(char ch: fir)
        idx[(int)ch] = 1;
    for(char ch: sec)
        idx[(int)ch] = 2;
    string pat, txt;
    vector<pair<int, string> > ans;
    cin >> pat;
    while(cin >> txt) {
        pair<int, string> tmp;
        tmp.first = calc(pat, txt);
        tmp.second = move(txt);
        int pos = 0;
        for( ; pos < (int)ans.size() && ans[pos].first <= tmp.first; ++pos);
        if(pos == 3)
            continue;
        ans.push_back(move(tmp));
        rotate(ans.begin() + pos, ans.end() - 1, ans.end());
        if(ans.size() > 3)
            ans.pop_back();
    }
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i].second;
        if(i + 1 == (int)ans.size())
            cout << endl;
        else
            cout << ' ';
    }
    return 0;
}
