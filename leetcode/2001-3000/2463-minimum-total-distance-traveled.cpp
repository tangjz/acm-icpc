class Solution {
public:
    long long minimumTotalDistance(vector<int>& A, vector<vector<int>>& B) {
        typedef long long LL;
        int n = A.size(), m = B.size();
        vector<LL> f(n + 1, LLONG_MAX), g(n + 1);
        f[0] = 0;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        for(auto &it: B) {
            for(int i = n; i >= 0; --i) {
                g[i] = f[i];
                if(f[i] == LLONG_MAX)
                    continue;
                LL adt = 0;
                for(int j = i + 1; j <= n && j - i <= it[1]; ++j) {
                    adt += abs(it[0] - A[j - 1]);
                    g[j] = min(g[j], f[i] + adt);
                }
            }
            f.swap(g);
        }
        return f.back();
    }
};
