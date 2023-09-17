class Solution {
public:
    long long findScore(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        priority_queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            que.push({-nums[i], -i});
        LL ans = 0;
        while(!que.empty()) {
            pair<int, int> cur = que.top();
            que.pop();
            int u = -cur.second;
            if(-cur.first != nums[u])
                continue;
            ans += nums[u];
            nums[u] = -1;
            if(u > 0)
                nums[u - 1] = -1;
            if(u + 1 < n)
                nums[u + 1] = -1;
        }
        return ans;
    }
};
