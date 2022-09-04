class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& mat, int dt) {
        int r = mat.size(), c = mat[0].size(), ans = INT_MIN;
        for(int i = 0; i < r; ++i) {
            vector<int> seq(c);
            for(int j = i; j < r; ++j) {
                int cur = 0;
                set<int> sp;
                for(int k = 0; k < c; ++k) {
                    seq[k] += mat[j][k];
                    sp.insert(cur);
                    // printf("put %d\n", cur);
                    cur += seq[k];
                    auto it = sp.lower_bound(cur - dt);
                    // printf("%d %d %d: cur %d low %d\n", i, j, k, cur, cur - dt);
                    if(it != sp.end()) {
                        // printf("found %d: %d\n", *it, cur - *it);
                        ans = max(ans, cur - *it);
                        if(ans == dt)
                            return ans;
                    }
                }
            }
        }
        return ans;
    }
};
