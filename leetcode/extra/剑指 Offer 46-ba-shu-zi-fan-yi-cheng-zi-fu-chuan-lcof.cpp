class Solution {
public:
    int translateNum(int num) {
        string buf = to_string(num);
        int n = buf.size();
        static int f[2], cur = 0, pre = 1;
        f[pre] = 0;
        f[cur] = 1;
        for(int i = 0; i < n; ++i) {
            swap(pre, cur);
            f[cur] = i > 0 && buf[i - 1] != '0' && (buf[i - 1] - '0') * 10 + (buf[i] - '0') < 26 ? f[cur] : 0;
            f[cur] += f[pre];
        }
        return f[cur];
    }
};
