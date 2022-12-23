class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        typedef long long LL;
        int n = nums.size();
        LL mid = 0;
        vector<int> ord(n);
        for(int i = 0; i < n; ++i) {
            ord[i] = i;
            mid += cost[i];
        }
        mid = (mid + 1) / 2;
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] < nums[v];
        });
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            mid -= cost[u];
            if(mid <= 0) {
                LL ans = 0;
                for(int j = 0; j < n; ++j)
                    ans += (LL)abs(nums[j] - nums[u]) * cost[j];
                return ans;
            }
        }
        return -1;
    }
};
