class Solution {
    typedef long long LL;
    LL calc(vector<int> &nums, int upp) {
        int cnt = 0;
        LL ans = 0;
        for(int x: nums) {
            if(x <= upp) {
                ans += ++cnt;
            } else {
                cnt = 0;
            }
        }
        return ans;
    }
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        return calc(nums, right) - calc(nums, left - 1);
    }
};
