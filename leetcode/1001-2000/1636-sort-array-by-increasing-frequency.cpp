class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        sort(nums.begin(), nums.end(), [&](int const &x, int const &y) {
            return make_pair(ctr[x], -x) < make_pair(ctr[y], -y);
        });
        return nums;
    }
};
