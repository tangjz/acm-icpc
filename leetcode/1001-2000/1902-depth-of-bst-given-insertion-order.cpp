class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        int n = order.size();
        vector<int> pL(n + 2), pR(n + 2), dep(n + 2);
        iota(pL.begin(), pL.end(), -1);
        iota(pR.begin(), pR.end(), 1);
        for(int i = n - 1; i >= 0; --i) {
            int u = order[i];
            pL[pR[u]] = pL[u];
            pR[pL[u]] = pR[u];
        }
        int ans = 0;
        for(int u: order) {
            dep[u] = max(dep[pL[u]], dep[pR[u]]) + 1;
            ans = max(ans, dep[u]);
            pL[pR[u]] = u;
            pR[pL[u]] = u;
        }
        return ans;
    }
};
