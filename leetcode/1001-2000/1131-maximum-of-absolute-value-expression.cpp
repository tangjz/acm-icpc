class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        const int INF = 0x3f3f3f3f;
        int ans = 0, n = arr1.size();
        vector<int> best(8, -INF);
        for(int i = 0; i < n; ++i) {
            static int seq[3];
            seq[0] = arr1[i];
            seq[1] = arr2[i];
            seq[2] = i;
            for(int j = 0; j < 8; ++j) {
                int val = 0;
                for(int k = 0; k < 3; ++k)
                    val += ((j >> k) & 1) ? seq[k] : -seq[k];
                best[j] = max(best[j], val);
                ans = max(ans, -val + best[j]);
                // printf("%d %d: %d %d: %d\n", i, j, val, best[j], -val + best[j]);
            }
        }
        return ans;
    }
};
