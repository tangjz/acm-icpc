class Solution {
public:
    int sumBase(int n, int k) {
        int ret = 0;
        for( ; n > 0; ret += n % k, n /= k);
        return ret;
    }
};
