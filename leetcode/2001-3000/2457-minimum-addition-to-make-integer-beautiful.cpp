class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target) {
        string buf = "0" + to_string(n - 1);
        int len = buf.size(), sum = 0;
        for(char ch: buf)
            sum += ch - '0';
        for(int i = len - 1; i >= 0; --i) {
            int d = buf[i] - '0';
            if(d + 1 < 10 && sum + 1 <= target) {
                ++buf[i];
                return stol(buf) - n;
            }
            buf[i] = '0';
            sum -= d;
        }
        return -1;
    }
};
