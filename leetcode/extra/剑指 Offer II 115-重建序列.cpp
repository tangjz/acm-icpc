class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        if(sequences.empty())
            return 0;
        int n = nums.size();
        vector<int> pos(n + 1);
        for(int i = 0; i < n; ++i)
            pos[nums[i]] = i;
        vector<int> deg(n), dp(n), que;
        vector<vector<int> > e(n);
        for(auto &vec: sequences) {
            int m = vec.size();
            for(int i = 0; i < m; ++i) {
                if(vec[i] < 0 || vec[i] > n)
                    return 0;
                vec[i] = pos[vec[i]];
                if(!i)
                    continue;
                if(vec[i - 1] >= vec[i])
                    return 0;
                e[vec[i - 1]].push_back(vec[i]);
                ++deg[vec[i]];
            }
        }
        for(int i = 0; i < n; ++i)
            if(!deg[i])
                que.push_back(i);
        for(int i = 0; i < n; ++i) {
            int u = que[i];
            if(dp[u] != i)
                return 0;
            for(int v: e[u]) {
                dp[v] = max(dp[v], dp[u] + 1);
                if(!(--deg[v]))
                    que.push_back(v);
            }
        }
        return 1;
    }
};
