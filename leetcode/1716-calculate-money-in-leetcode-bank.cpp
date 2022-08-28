class Solution {
public:
    int totalMoney(int n) {
        int ans = 1, cur = 1;
        for(int i = 1; i < n; ++i) {
            cur += i % 7 ? 1 : -5;
            ans += cur;
        }
        return ans;
    }
};
