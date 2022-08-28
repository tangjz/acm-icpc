class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        const int maxd = 26;
        int n = s.size();
        vector<int> ctr(maxd), rem(maxd), nxt(n);
        vector<bool> vis(n);
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            ++ctr[o];
        }
        for(int i = 0; i < maxd; ++i) {
            rem[i] = ctr[i] >> 1;
        }
        int ans = 0, pos = 0;
        vector<vector<int> > cand(maxd);
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            if(!rem[o])
                continue;
            vis[i] = 1;
            --rem[o];
            nxt[i] = pos;
            cand[o].push_back(n - 1 - pos);
            // printf("ch %c: %d %d\n", s[i], pos, n - 1 - pos);
            ++pos;
        }
        if(n & 1)
            for(int i = 0; i < n; ++i) {
                if(vis[i])
                    continue;
                int o = s[i] - 'a';
                if(ctr[o] & 1) {
                    vis[i] = 1;
                    --rem[o];
                    nxt[i] = pos;
                    // printf("ch %c: %d\n", s[i], pos);
                    ++pos;
                    break;
                }
            }
        for(int i = 0; i < n; ++i)
            if(!vis[i]) {
                int o = s[i] - 'a';
                nxt[i] = cand[o].back();
                // printf("match %c: %d\n", s[i], cand[o].back());
                cand[o].pop_back();
            }
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < n - i; ++j)
                if(nxt[j - 1] > nxt[j]) {
                    swap(nxt[j - 1], nxt[j]);
                    ++ans;
                }
        return ans;
    }
};
