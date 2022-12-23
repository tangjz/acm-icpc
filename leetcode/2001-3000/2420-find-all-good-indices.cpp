class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ctr(n);
        for(int i = 1, c = 0; i < n; ++i) {
            if(i >= k) {
                // printf("%d: %d\n", i, c);
                if(c == k - 1)
                    ++ctr[i];
                c -= nums[i - k] >= nums[i - k + 1];
            }
            c += nums[i - 1] >= nums[i];
        }
        for(int i = 1, c = 0; i < n; ++i) {
            c += nums[i - 1] <= nums[i];
            if(i >= k) {
                c -= nums[i - k] <= nums[i - k + 1];
                // printf("%d: %d\n", i, c);
                if(c == k - 1)
                    ++ctr[i - k];
            }
        }
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            if(ctr[i] == 2)
                ret.push_back(i);
        return ret;
    }
};
