class Solution {
public:
    int minOperations(int n) {
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += abs(i + i + 1 - n);
        return ans >> 1;
    }
};
