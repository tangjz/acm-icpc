class Solution {
public:
    string boldWords(vector<string>& words, string s) {
        const int maxs = (int)1e5 + 1, maxd = 52;
        static int idx[1 << 8 | 1];
        static int tot, nxt[maxs][maxd + 1], que[maxs], len[maxs];
        if(!idx['a']) {
            int ctr = 0;
            for(char ch = 'a'; ch <= 'z'; ++ch)
                idx[ch] = ctr++;
            for(char ch = 'A'; ch <= 'Z'; ++ch)
                idx[ch] = ctr++;
        }
        tot = 0;
        len[tot] = 0;
        memset(nxt[tot++], 0, sizeof(nxt[0]));
        for(auto &it: words) {
            int rt = 0;
            for(char ch: it) {
                int o = idx[ch];
                if(!nxt[rt][o]) {
                    nxt[rt][o] = tot;
                    len[tot] = 0;
                    memset(nxt[tot++], 0, sizeof(nxt[0]));
                }
                rt = nxt[rt][o];
            }
            len[rt] = max(len[rt], (int)it.size());
        }
        tot = 0;
        for(int i = 0; i < maxd; ++i)
            if(nxt[0][i])
                que[tot++] = nxt[0][i];
        for(int i = 0; i < tot; ++i) {
            int u = que[i];
            for(int j = 0; j < maxd; ++j) {
                if(!nxt[u][j])
                    continue;
                int v = nxt[u][j];
                que[tot++] = v;
                int &k = nxt[v][maxd];
                for(k = nxt[u][maxd]; k && !nxt[k][j]; k = nxt[k][maxd]);
                if(nxt[k][j])
                    k = nxt[k][j];
                len[v] = max(len[v], len[k]);
            }
        }
        
        const int maxn = (int)1e3 + 1, maxl = (int)1e4 + 1;
        static int bold[maxn];
        static char buf[maxl];
        int n = s.size();
        memset(bold, 0, n * sizeof(int));
        for(int i = 0, j = 0; i < n; ++i) {
            int o = idx[s[i]];
            for( ; j && !nxt[j][o]; j = nxt[j][maxd]);
            if(nxt[j][o])
                j = nxt[j][o];
            if(len[j]) {
                ++bold[i - len[j] + 1];
                --bold[i + 1];
            }
        }
        for(int i = 0; i < n; ++i) {
            bold[i + 1] += bold[i];
            bold[i] = !!bold[i];
        }
        tot = 0;
        const char *pre = "<b>", *suf = "</b>";
        for(int i = 0, j, k; i < n; ) {
            j = i;
            if(bold[j])
                for(k = 0; pre[k]; buf[tot++] = pre[k++]);
            for( ; i < n && bold[i] == bold[j]; ++i)
                buf[tot++] = s[i];
            if(bold[j])
                for(k = 0; suf[k]; buf[tot++] = suf[k++]);
        }
        buf[tot] = '\0';
        return buf;
    }
};
