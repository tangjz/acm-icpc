class Solution {
public:
    string smallestSubsequence(string s, int k, char ch, int m) {
        const int maxc = 26;
        int n = s.size();
        vector<int> ctr(n + 1);
        vector<vector<int> > nxt(n + 1, vector<int>(maxc, n + 1));
        ctr[n] = 0;
        for(int i = n - 1; i >= 0; --i) {
            ctr[i] = ctr[i + 1] + (s[i] == ch);
            for(int j = 0; j < maxc; ++j)
                nxt[i][j] = nxt[i + 1][j];
            nxt[i][(int)(s[i] - 'a')] = i;
        }
        string t = "";
        for(int i = 0, p = 0; i < k; ++i) {
            for(int j = 0; j < maxc; ++j) {
                int o = nxt[p][j];
                char c = 'a' + j;
                if(o >= n || ctr[o] < m || k - i - 1 < m - (c == ch) || n - o - 1 < k - i - 1)
                    continue;
                t += 'a' + j;
                m -= c == ch;
                p = o + 1;
                break;
            }
        }
        return t;
    }
};
