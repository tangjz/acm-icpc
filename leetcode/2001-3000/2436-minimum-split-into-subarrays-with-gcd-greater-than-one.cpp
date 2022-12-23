class Solution {
public:
    int minimumSplits(vector<int>& nums) {
        int ans = 0, cur = 0;
        for(int x: nums) {
            cur = gcd(cur, x);
            if(cur == 1) {
                ++ans;
                cur = x;
            }
        }
        return ++ans;
    }
};
