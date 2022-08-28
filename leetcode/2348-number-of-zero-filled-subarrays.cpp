class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long ans = 0;
        int cnt = 0;
        for(int x: nums) {
            if(!x) {
                ans += ++cnt;
            } else {
                cnt = 0;
            }
        }
        return ans;
    }
};
