class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> ctr;
        vector<int> fir;
        for(int x: nums)
            ctr[x] += x;
        for(auto &it: ctr)
            if(!ctr.count(it.first - 1))
                fir.push_back(it.first);
        int ans = 0;
        for(int s: fir) {
            int dp[2] = {0, 0};
            for(int x = s; ; ++x) {
                auto it = ctr.find(x);
                if(it == ctr.end())
                    break;
                int u = max(dp[0], dp[1]);
                int v = max(dp[1], dp[0] + (it -> second));
                dp[0] = u;
                dp[1] = v;
            }
            ans += max(dp[0], dp[1]);
        }
        return ans;
    }
};
