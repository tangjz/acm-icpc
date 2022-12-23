class Solution {
public:
    int longestSquareStreak(vector<int>& A) {
        typedef long long LL;
        int n = A.size(), ans = 0;
        sort(A.begin(), A.end());
        unordered_map<LL, int> dp;
        for(int x: A) {
            auto it = dp.find(x);
            int v = it == dp.end() ? 1 : (it -> second) + 1;
            int &v2 = dp[(LL)x * x];
            v2 = max(v2, v);
            ans = max(ans, v2);
        }
        return ans < 2 ? -1 : ans;
    }
};
