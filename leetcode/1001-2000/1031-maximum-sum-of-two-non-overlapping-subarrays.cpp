class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size(), ans = 0;
        for(int i = 0; i < 2; ++i) {
            vector<int> psum = {0};
            for(int x: nums) {
                psum.push_back(psum.back() + x);
            }
            vector<int> suf(n + 1, INT_MIN);
            for(int i = n - secondLen; i >= 0; --i) {
                suf[i] = max(suf[i + 1], psum[i + secondLen] - psum[i]);
            }
            for(int i = firstLen; i <= n - secondLen; ++i) {
                ans = max(ans, psum[i] - psum[i - firstLen] + suf[i]);
            }
            reverse(nums.begin(), nums.end());
        }
        return ans;
    }
};
