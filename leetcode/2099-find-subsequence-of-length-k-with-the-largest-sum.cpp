class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] > nums[v];
        });
        ord.resize(k);
        sort(ord.begin(), ord.end());
        vector<int> ret;
        for(int x: ord) {
            ret.push_back(nums[x]);
        }
        return ret;
    }
};
