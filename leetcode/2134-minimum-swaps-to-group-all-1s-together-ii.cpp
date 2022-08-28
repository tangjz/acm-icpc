class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int ctr = 0;
        for(int x: nums)
            ctr += x;
        if(!ctr)
            return 0;
        int n = nums.size();
        int ans = n;
        int cnt = 0;
        for(int i = 0; i < ctr; ++i)
            cnt += !nums[i];
        for(int i = 0; i < n; ++i) {
            ans = min(ans, cnt);
            cnt -= !nums[i];
            cnt += !nums[(i + ctr) % n];
        }
        return ans;
    }
};
