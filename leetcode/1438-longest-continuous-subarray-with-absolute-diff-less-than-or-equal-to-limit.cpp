class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = (int)nums.size(), ans = 1;
        multiset<int> Hash;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && (i == j || *Hash.rbegin() - *Hash.begin() <= limit); ++j)
                Hash.insert(nums[j]);
            int len = j - i - (*Hash.rbegin() - *Hash.begin() > limit);
            ans = max(ans, len);
            Hash.erase(Hash.find(nums[i]));
        }
        return ans;
    }
};
