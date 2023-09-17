class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        const int maxd = 26;
        int n = (int)s.length(), m = (int)p.length();
        vector<int> ret, pat(maxd, 0);
        for(char ch : p)
            ++pat[(int)(ch - 'a')];
        vector<vector<int> > sum;
        sum.push_back(vector<int>(maxd, 0));
        for(int i = 0; i < n; ++i) {
            sum.push_back(sum.back());
            ++sum.back()[(int)(s[i] - 'a')];
            if(i >= m - 1) {
                bool chk = 1;
                for(int j = 0; chk && j < maxd; ++j)
                    chk &= pat[j] == sum[i + 1][j] - sum[i - m + 1][j];
                if(chk)
                    ret.push_back(i - m + 1);
            }
        }
        return ret;
    }
};
