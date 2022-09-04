class Solution {
public:
    long long countSubarrays(vector<int>& nums) {
        typedef long long LL;
        int cnt = 0, las = INT_MAX;
        LL ans = 0;
        for(int x: nums) {
            if(las < x) {
                ++cnt;
            } else {
                cnt = 1;
            }
            ans += cnt;
            las = x;
        }
        return ans;
    }
};
