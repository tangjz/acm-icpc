class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        typedef long long LL;
        LL ans = 0;
        unordered_map<int, int> ctr;
        int cur = 0;
        for(int x: nums) {
            ++ctr[cur];
            cur ^= x;
            ans += ctr[cur];
        }
        return ans;
    }
};
