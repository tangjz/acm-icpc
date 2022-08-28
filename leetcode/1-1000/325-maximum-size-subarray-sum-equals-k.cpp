class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0, cur = 0;
        unordered_map<int, int> Hash;
        for(int i = 0; i < n; ++i) {
            Hash.insert({cur, i});
            cur += nums[i];
            long long target = cur;
            target -= k;
            if(target < INT_MIN || target > INT_MAX)
                continue;
            auto it = Hash.find((int)target);
            if(it != Hash.end())
                ans = max(ans, i - (it -> second) + 1);
        }
        return ans;
    }
};
