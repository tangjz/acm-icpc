class Solution {
public:
    int maximumProduct(vector<int>& nums, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0; k > 0; ) {
            for( ; i + 1 < n && nums[i] == nums[i + 1]; ++i);
            for(int j = i; j >= 0 && k > 0; --j, --k)
                ++nums[j];
        }
        int ans = 1;
        for(int x: nums)
            ans = (LL)ans * x % mod;
        return ans;
    }
};
