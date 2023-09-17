class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        typedef long long LL;
        int n = nums.size();
        LL ans = LLONG_MAX;
        vector<int> c = nums;
        for(int i = 0; i < n; ++i) {
            LL cur = (LL)x * i;
            for(int j = 0, k = i; j < n; ++j, (++k) == n && (k = 0)) {
                c[j] = min(c[j], nums[k]);
                cur += c[j];
            }
            ans = min(ans, cur);
        }
        return ans;
    }
};
