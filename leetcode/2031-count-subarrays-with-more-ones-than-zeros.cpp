class Solution {
public:
    int subarraysWithMoreZerosThanOnes(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        vector<int> bits(n + n);
        for(int i = 0, s = 0; i < n; ++i) {
            for(int x = s + n + 1; x <= n + n; x += x & -x)
                ++bits[x - 1];
            s += nums[i] > 0 ? 1 : -1;
            for(int x = s + n; x > 0; x -= x & -x)
                ans += bits[x - 1];
        }
        return ans % ((int)1e9 + 7);
    }
};
