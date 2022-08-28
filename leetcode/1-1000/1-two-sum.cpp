class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] < nums[v];
        });
        for(int i = 0, j = n - 1; i < j; ++i) {
            for( ; i < j && nums[ord[i]] + nums[ord[j]] > target; --j);
            if(i < j && nums[ord[i]] + nums[ord[j]] == target)
                return {ord[i], ord[j]};
        }
        return {};
    }
};
