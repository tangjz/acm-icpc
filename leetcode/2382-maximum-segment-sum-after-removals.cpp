class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& A, vector<int>& B) {
        typedef long long LL;
        int n = A.size(), m = B.size();
        LL ans = 0;
        vector<int> pL(n), pR(n);
        vector<LL> psum(n + 1);
        vector<bool> vis(n);
        for(int x: B)
            vis[x] = 1;
        for(int i = 0; i < n; ++i) {
            if(!vis[i]) {
                vis[i] = 1;
                B.push_back(i);
            }
            psum[i + 1] = psum[i] + A[i];
        }
        vector<LL> ret(m);
        while(!B.empty()) {
            int u = B.back();
            B.pop_back();
            if(B.size() < m)
                ret[B.size()] = ans;
            vis[u] = 0;
            int L = u, R = u;
            if(L > 0 && !vis[L - 1]) {
                L = pL[L - 1];
            }
            if(R + 1 < n && !vis[R + 1]) {
                R = pR[R + 1];
            }
            ans = max(ans, psum[R + 1] - psum[L]);
            pL[R] = L;
            pR[L] = R;
        }
        return ret;
    }
};
