class Solution {
public:
    int getKthNum(int k) {
        typedef long long LL;
        int len = 1, pw = 10;
        while(k > (LL)len * (pw - pw / 10)) {
            k -= len * (pw - pw / 10);
            ++len;
            pw *= 10;
        }
        int val = (k - 1) / len;
        k -= val * len;
        val += pw / 10;
        string buf = to_string(val);
        return buf[k - 1] - '0';
    }
};
