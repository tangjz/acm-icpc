class Solution {
public:
    int reachNumber(int target) {
        int ans = 0, sum = 0;
        target = abs(target);
        for( ; !(target <= sum && !((sum - target) & 1)); sum += ++ans);
        return ans;
    }
};
