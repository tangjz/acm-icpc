class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            int com = 0;
            for(int j = i; j < n; ++j) {
                com = gcd(com, nums[j]);
                ans += com == k;
                if(com < k)
                    break;
            }
        }
        return ans;
    }
};
