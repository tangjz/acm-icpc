class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ret = 0, mx = 0;
        for(int x : nums) {
            if(!x)
                continue;
            ret += __builtin_popcount(x);
            mx = max(mx, 31 - __builtin_clz(x));
        }
        return ret + mx;
    }
};
