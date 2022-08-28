class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        const int maxd = 26;
        int n = s.size(), m = queryCharacters.size();
        vector<int> pL(n, -1), pR(n, -1), upp(maxd);
        set<int> rht[maxd];
        set<pair<int, int> > sp[maxd];
        for(int i = 0, j; i < n; i = j) {
            int o = s[i] - 'a';
            for(j = i; j < n && s[i] == s[j]; ++j);
            pL[j - 1] = i;
            pR[i] = j - 1;
            rht[o].insert(j - 1);
            sp[o].insert({j - i, i});
        }
        for(int i = 0; i < maxd; ++i) {
            upp[i] = sp[i].empty() ? 0 : sp[i].rbegin() -> first;
        }
        vector<int> ans;
        for(int i = 0; i < m; ++i) {
            int pos = queryIndices[i];
            char ch = queryCharacters[i];
            if(s[pos] != ch) {
                int u = s[pos] - 'a', v = ch - 'a';
                int R = *rht[u].lower_bound(pos);
                int L = pL[R];
                
                rht[u].erase(R);
                sp[u].erase({R - L + 1, L});
                pL[R] = pR[L] = -1;
                
                int nL = pos, nR = pos;
                
                if(pos > L) {
                    rht[u].insert(pos - 1);
                    sp[u].insert({pos - L, L});
                    pL[pos - 1] = L;
                    pR[L] = pos - 1;
                } else if(pos > 0 && s[pos - 1] == ch) {
                    int tR = pos - 1, tL = pL[tR];
                    rht[v].erase(pos - 1);
                    sp[v].erase({pos - tL, tL});
                    pL[tR] = pR[tL] = -1;
                    nL = tL;
                }
                
                if(pos < R) {
                    rht[u].insert(R);
                    sp[u].insert({R - pos, pos + 1});
                    pL[R] = pos + 1;
                    pR[pos + 1] = R;
                } else if(pos + 1 < n && s[pos + 1] == ch) {
                    int tL = pos + 1, tR = pR[tL];
                    rht[v].erase(tR);
                    sp[v].erase({tR - pos, pos + 1});
                    pL[tR] = pR[tL] = -1;
                    nR = tR;
                }
                
                s[pos] = ch;
                rht[v].insert(nR);
                sp[v].insert({nR - nL + 1, nL});
                pL[nR] = nL;
                pR[nL] = nR;
                
                upp[u] = sp[u].empty() ? 0 : sp[u].rbegin() -> first;
                upp[v] = sp[v].empty() ? 0 : sp[v].rbegin() -> first;
            }
            int best = 0;
            for(int j = 0; j < maxd; ++j)
                best = max(best, upp[j]);
            ans.push_back(best);
        }
        return ans;
    }
};
