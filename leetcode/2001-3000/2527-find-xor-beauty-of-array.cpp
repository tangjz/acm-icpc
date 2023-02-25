class Solution {
public:
    int xorBeauty(vector<int>& nums) {
        int ans = 0, n = nums.size() & 1, mx = *max_element(nums.begin(), nums.end());
        for(int i = 1; i <= mx; i <<= 1) {
            int c = 0;
            for(int x: nums)
                c += !!(x & i);
            c &= 1;
            if((c * (n * n - (n - c) * (n - c))) & 1)
                ans ^= i;
        }
        return ans;
    }
};
