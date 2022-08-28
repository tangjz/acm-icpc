class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int upp = *max_element(nums.begin(), nums.end());
        vector<int> psum(upp + 2);
        for(int x: nums)
            ++psum[x];
        for(int i = upp; i > 0; --i)
            psum[i] += psum[i + 1];
        const int mod = (int)1e9 + 7;
        long long ans = 0;
        for(int i = 1; i <= upp; ++i)
            for(int j = i; j <= upp; j += i)
                ans += 1LL * (psum[i] - psum[i + 1]) * psum[j];
        return ans % mod;
    }
};
