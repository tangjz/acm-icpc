class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int> deg(n);
        for(auto &it: roads) {
            ++deg[it[0]];
            ++deg[it[1]];
        }
        sort(deg.begin(), deg.end());
        long long ans = 0;
        for(int i = 0; i < n; ++i)
            ans += (i + 1LL) * deg[i];
        return ans;
    }
};
