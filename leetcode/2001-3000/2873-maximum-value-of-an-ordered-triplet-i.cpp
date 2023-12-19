class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        typedef long long LL;
        int pre = (int)-1e7, dif = 0;
        LL ans = 0;
        for(int x: nums) {
            ans = max(ans, (LL)dif * x);
            dif = max(dif, pre - x);
            pre = max(pre, x);
        }
        return ans;
    }
};
