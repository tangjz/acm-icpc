class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        vector<int> ctr(n + 1);
        for(int j = 0, c = 0; j < n; ++j) {
            c ^= ctr[j];
            if((c ^ nums[j]) == 1)
                continue;
            if(j > n - k)
                return -1;
            ++ans;
            c ^= 1;
            ctr[j] ^= 1;
            ctr[j + k] ^= 1;
        }
        return ans;
    }
};
