class Solution {
public:
    int findNthDigit(int n) {
        typedef long long LL;
        int len = 1, pw = 10;
        while(n > (LL)len * (pw - pw / 10)) {
            n -= len * (pw - pw / 10);
            ++len;
            pw *= 10;
        }
        int val = (n - 1) / len;
        n -= val * len;
        val += pw / 10;
        string buf = to_string(val);
        return buf[n - 1] - '0';
    }
};
