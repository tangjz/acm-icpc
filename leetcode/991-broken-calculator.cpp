class Solution {
public:
    int brokenCalc(int startValue, int target) {
        int ans = 0;
        while(target > startValue) {
            if(target & 1) {
                ++target;
                ++ans;
            }
            target >>= 1;
            ++ans;
        }
        ans += startValue - target;
        return ans;
    }
};
