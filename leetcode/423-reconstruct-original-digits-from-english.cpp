class Solution {
public:
    string originalDigits(string s) {
        static const int maxd = 10, maxc = 26;
        static const string digits[maxd] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        static int ctr[maxc], out[maxd];
        memset(ctr, 0, sizeof ctr);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        // "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
        // 0z2w4u6x8g <= z0 e0135789 r034 o0124 n179 t238 w2 h38 f45 u4 i5689 v57 s67 x6 g8
        // 1o3h5f7s <= e13579 r3 o1 n179 t3 h3 f5 i59 v57 s7
        // 9i <= e9 n9 i9
        out[0] = ctr[(int)('z' - 'a')];
        out[2] = ctr[(int)('w' - 'a')];
        out[4] = ctr[(int)('u' - 'a')];
        out[6] = ctr[(int)('x' - 'a')];
        out[8] = ctr[(int)('g' - 'a')];
        out[1] = ctr[(int)('o' - 'a')] - out[0] - out[2] - out[4];
        out[3] = ctr[(int)('h' - 'a')] - out[8];
        out[5] = ctr[(int)('f' - 'a')] - out[4];
        out[7] = ctr[(int)('s' - 'a')] - out[6];
        out[9] = ctr[(int)('i' - 'a')] - out[5] - out[6] - out[8];
        s = "";
        for(int i = 0; i < maxd; ++i)
            while(out[i]--)
                s += digits[i];
        return s;
    }
};
