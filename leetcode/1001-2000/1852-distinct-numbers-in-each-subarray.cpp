class Solution {
public:
    vector<int> distinctNumbers(vector<int>& nums, int k) {
        int n = nums.size(), m = 0;
        unordered_map<int, int> ctr;
        vector<int> ans;
        ans.reserve(n - m + 1);
        for(int i = 0; i < n; ++i) {
            m += !(ctr[nums[i]]++);
            if(i >= k - 1) {
                ans.push_back(m);
                m -= !(--ctr[nums[i - k + 1]]);
            }
        }
        return ans;
    }
};
