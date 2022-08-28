class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        const int maxc = 26;
        int n = s.size();
        vector<vector<int> > nxt(n + 1, vector<int>(maxc, n));
        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j < maxc; ++j)
                nxt[i][j] = nxt[i + 1][j];
            nxt[i][(int)(s[i] - 'a')] = i;
        }
        vector<string> f = {""};
        for(int i = 0; i < 8; ++i) {
            vector<string> g = {};
            for(auto &it: f) {
                string t = it;
                t.push_back('a');
                for(int j = 0; j < maxc; ++j) {
                    int pos = 0;
                    bool bad = 0;
                    // printf("test %s:", t.c_str());
                    for(int x = 0; !bad && x < k; ++x) {
                        for(int y = 0; !bad && y <= i; ++y) {
                            pos = nxt[pos][(int)(t[y] - 'a')];
                            bad |= pos == n;
                            // printf(" %d (%d)", pos, bad);
                            ++pos;
                        }
                    }
                    // puts("");
                    if(!bad) {
                        g.push_back(t);
                    }
                    t.back() += 1;
                }
            }
            if(g.empty())
                break;
            f = move(g);
        }
        return f.back();
    }
};
