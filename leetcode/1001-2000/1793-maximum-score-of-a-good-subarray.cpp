class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = (int)nums.size();
        map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[-nums[i]].push_back(i);
        vector<int> pL(n, -1), pR(n, -1);
        int ans = 0;
        for(auto &it: pos)
            for(int i: it.second) {
                int u = pL[i] = i, v = pR[i] = i, w;
                if(i > 0 && (w = pL[i - 1]) != -1) {
                    pR[w] = v;
                    pL[v] = w;
                    u = w;
                }
                if(i + 1 < n && (w = pR[i + 1]) != -1) {
                    pL[w] = u;
                    pR[u] = w;
                    v = w;
                }
                // printf("%d: %d %d\n", i, u, v);
                if(u <= k && k <= v)
                    ans = max(ans, nums[i] * (v - u + 1));
            }
        return ans;
    }
};
