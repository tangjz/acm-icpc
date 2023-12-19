class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int upp, vector<vector<int>>& com, vector<int>& a, vector<int>& w) {
        typedef long long LL;
        int ans = 0;
        for(auto &it: com) {
            int L = 0, R = (int)1e9;
            while(L < R) {
                int M = (L + R + 1) / 2;
                LL adt = 0;
                for(int i = 0; i < n; ++i)
                    adt += max((LL)M * it[i] - a[i], 0LL) * w[i];
                if(adt > upp) {
                    R = M - 1;
                } else {
                    L = M;
                }
            }
            ans = max(ans, L);
        }
        return ans;
    }
};
