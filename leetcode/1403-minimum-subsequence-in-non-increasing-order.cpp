class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int sum = 0;
        for(int x : nums)
            sum += x;
        int cur = 0;
        vector<int> ret;
        for(int x : nums) {
            ret.push_back(x);
            cur += x;
            if(cur > sum - cur)
                break;
        }
        return ret;
    }
};
