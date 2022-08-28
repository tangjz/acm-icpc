class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size(), ans = 0;
        vector<int> ctr(n + 1);
        for(int i = 0, s = 0; i < n; ++i) {
            ++ctr[s];
            s += nums[i];
            if(s >= goal)
                ans += ctr[s - goal];
        }
        return ans;
    }
};
