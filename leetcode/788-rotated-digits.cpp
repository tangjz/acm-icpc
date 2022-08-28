class Solution {
public:
    int rotatedDigits(int n) {
        static const int typ[] = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
        string buf = to_string(n + 1);
        int m = buf.size(), ans = 0;
        vector<int> pw3(m), pw7(m);
        pw3[0] = pw7[0] = 1;
        for(int i = 1; i < m; ++i) {
            pw3[i] = pw3[i - 1] * 3;
            pw7[i] = pw7[i - 1] * 7;
        }
        for(int i = m - 1, has = 0; i >= 0; --i) {
            int d = buf[m - 1 - i] - '0';
            for(int j = 0; j < d; ++j)
                if(typ[j] != -1) {
                    int has2 = has | typ[j];
                    ans += pw7[i] - (has2 ? 0 : pw3[i]);
                }
            if(typ[d] == -1)
                break;
            has |= typ[d];
        }
        return ans;
    }
};
