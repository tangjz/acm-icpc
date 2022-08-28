#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = (int)word1.size(), m = (int)word2.size();
        if(n < m) {
            swap(n, m);
            word1.swap(word2);
        }
        vector<int> dp;
        for(int i = 0; i <= m; ++i)
            dp.push_back(i);
        for(int i = 1; i <= n; ++i) {
            int las = dp.front(), cur;
            dp.front() = i;
            for(int j = 1; j <= m; ++j) {
                cur = dp[j];
                dp[j] = min(min(dp[j - 1], cur) + 1, las + (word1[i - 1] != word2[j - 1]));
                las = cur;
            }
        }
        return dp[m];
    }
} obj;

int main() {
    string s;
    cin >> s;
    auto it = s.find(',');
    cout << obj.minDistance(s.substr(0, it), s.substr(it + 1)) << endl;
    return 0;
}
