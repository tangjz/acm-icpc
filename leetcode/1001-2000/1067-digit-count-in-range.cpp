class Solution {
    int calc(int d, int n) {
        string buf = to_string(n);
        reverse(buf.begin(), buf.end());
        int ans = 0, m = buf.size(), pw = 1, c = 0;
        for(int i = 0; i < m; ++i)
            c += buf[i] - '0' == d;
        for(int i = 0; i < m; ++i, pw *= 10) {
            int upp = buf[i] - '0';
            c -= upp == d;
            for(int j = i + 1 < m ? 0 : 1; j < upp; ++j) {
                ans += (c + (j == d)) * pw;
                ans += i * (pw / 10);
            }
            if(i + 1 < m)
                for(int j = 1; j < 10; ++j) {
                    ans += (j == d) * pw;
                    ans += i * (pw / 10);
                }
        }
        return ans;
    }
public:
    int digitsCount(int d, int low, int high) {
        return calc(d, high + 1) - calc(d, low);
    }
};
