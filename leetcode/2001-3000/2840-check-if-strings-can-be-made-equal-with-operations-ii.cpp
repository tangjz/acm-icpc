class Solution {
public:
    bool checkStrings(string s1, string s2) {
        static const int maxc = 26;
        static int ctr[2][maxc + 1];
        memset(ctr, 0, sizeof ctr);
        int n = s1.size(), m = s2.size();
        for(int i = 0; i < n; ++i) {
            int o = s1[i] - 'a';
            ++ctr[i & 1][o];
        }
        for(int i = 0; i < m; ++i) {
            int o = s2[i] - 'a';
            --ctr[i & 1][o];
        }
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < maxc; ++j)
                if(ctr[i][j])
                    return 0;
        return 1;
    }
};
