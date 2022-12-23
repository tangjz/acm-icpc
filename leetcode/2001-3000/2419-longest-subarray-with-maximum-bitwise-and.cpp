class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int ans = 0, cnt = 0, best = 0;
        for(int x: nums) {
            if(best < x) {
                best = x;
                ans = cnt = 0;
            }
            if(best == x) {
                ++cnt;
            } else {
                cnt = 0;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};
