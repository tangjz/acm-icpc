class Solution {
public:
    string thousandSeparator(int num) {
        string buf = to_string(num);
        int n = buf.size(), m = n + (n - 1) / 3;
        buf.resize(m);
        for(int i = n - 1, j = m - 1; i >= 3; ) {
            for(int k = 0; k < 3; ++k)
                buf[j--] = buf[i--];
            buf[j--] = '.';
        }
        return buf;
    }
};
