class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        const int maxd = 26, maxn = (int)5e4 + 1;
        int n = s.size();
        static int nxt[maxd + 1][maxn];
        for(int i = 0; i < maxd; ++i)
            nxt[i][n] = n;
        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j < maxd; ++j)
                nxt[j][i] = nxt[j][i + 1];
            nxt[(int)(s[i] - 'a')][i] = i;
        }
        int ans = 0;
        for(auto &buf: words) {
            int pos = -1;
            for(char ch: buf) {
                pos = nxt[(int)(ch - 'a')][pos + 1];
                if(pos >= n)
                    break;
            }
            ans += pos < n;
        }
        return ans;
    }
};
