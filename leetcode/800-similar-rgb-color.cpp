class Solution {
public:
    string similarRGB(string color) {
        int seq[3] = {};
        auto toInt = [&](char ch) {
            return isdigit(ch) ? (ch - '0') : (ch - 'a' + 10);
        };
        auto toChar = [&](int x) {
            return x < 10 ? ('0' + x) : ('a' + (x - 10));
        };
        for(int i = 0; i < 3; ++i) {
            seq[i] = toInt(color[i + i + 1]) << 4 | toInt(color[i + i + 2]);
            int L = seq[i] / 17 * 17, R = L + 17;
            if(R >= 256 || (seq[i] - L <= R - seq[i])) {
                seq[i] = L;
            } else {
                seq[i] = R;
            }
            color[i + i + 1] = color[i + i + 2] = toChar(seq[i] & 15);
        }
        return color;
    }
};
