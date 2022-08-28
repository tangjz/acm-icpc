class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int n = nums.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            bool good = 0;
            for(int j = max(i - k, 0); !good && j <= min(i + k, n - 1); ++j)
                good |= nums[j] == key;
            if(good)
                ret.push_back(i);
        }
        return ret;
    }
};
