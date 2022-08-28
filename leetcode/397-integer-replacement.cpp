class Solution {
public:
    int integerReplacement(long long n) {
        if(n == 1)
            return 0;
        static unordered_map<long long, int> stp;
        int &ret = stp[n];
        if(!ret) {
            if(n & 1) {
                ret = INT_MAX;
                int lft = integerReplacement(n - 1);
                int rht = integerReplacement(n + 1);
                ret = min(lft, rht) + 1;
            } else {
                ret = integerReplacement(n >> 1) + 1;
            }
        }
        return ret;
    }
};
