class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end()) + 1;
        vector<int> ctr(mx);
        for(int x: nums)
            ++ctr[x];
        for(int i = 1; i < mx; ++i)
            for(int j = i + i; j < mx; j += i)
                ctr[i] += ctr[j];
        int ans = 0;
        for(int i = 1; i < mx; ++i) {
            bool chk = ctr[i] > 0;
            for(int j = i + i; chk && j < mx; j += i)
                chk &= ctr[i] > ctr[j];
            ans += chk;
        }
        return ans;
    }
};
