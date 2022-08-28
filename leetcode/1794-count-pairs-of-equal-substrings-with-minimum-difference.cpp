class Solution {
public:
    int countQuadruples(string A, string B) {
        const int maxd = 26;
        int n = A.size(), m = B.size();
        vector<int> pos1(maxd, INT_MAX), pos2(maxd, INT_MIN);
        for(int i = 0; i < n; ++i) {
            int o = A[i] - 'a';
            pos1[o] = min(pos1[o], i);
        }
        for(int i = 0; i < m; ++i) {
            int o = B[i] - 'a';
            pos2[o] = max(pos2[o], i);
        }
        int ans = 0, best = INT_MAX;
        for(int i = 0; i < maxd; ++i) {
            if(pos1[i] == INT_MAX || pos2[i] == INT_MIN)
                continue;
            int cur = pos1[i] - pos2[i];
            if(cur < best) {
                best = cur;
                ans = 0;
            }
            ans += cur == best;
        }
        return ans;
    }
};
