class Solution {
public:
    int meetRequirement(int n, vector<vector<int>>& lights, vector<int>& requirement) {
        vector<int> ctr(n + 1);
        for(auto &it: lights) {
            int L = max(0, it[0] - it[1]), R = min(n - 1, it[0] + it[1]);
            ++ctr[L];
            --ctr[R + 1];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += ctr[i] >= requirement[i];
            ctr[i + 1] += ctr[i];
        }
        return ans;
    }
};
