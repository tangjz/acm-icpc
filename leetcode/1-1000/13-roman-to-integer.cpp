class Solution {
public:
    int romanToInt(string s) {
        const int maxd = 7, val[maxd] = {1, 5, 10, 50, 100, 500, 1000};
        const char *pat = "IVXLCDM";
        int n = s.size(), ans = 0;
        for(int i = 0, j; i < n; ++i) {
            for(j = 0; j < maxd && s[i] != pat[j]; ++j);
            if(i + 1 < n && j + 2 < maxd && (s[i + 1] == pat[j + 1] || s[i + 1] == pat[j + 2])) {
                int k = j + 1;
                k += s[i + 1] != pat[k];
                ans += val[k] - val[j];
                ++i;
                continue;
            }
            ans += val[j];
        }
        return ans;
    }
};
