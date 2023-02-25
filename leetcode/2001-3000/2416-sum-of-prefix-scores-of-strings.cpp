class Solution {
    static const int maxd = 26;
    struct Node {
        int cnt, nxt[maxd + 1];
    };
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        vector<Node> pool;
        pool.push_back({});
        for(auto &it: words) {
            int rt = 0;
            for(char ch: it) {
                int o = ch - 'a';
                if(!pool[rt].nxt[o]) {
                    pool[rt].nxt[o] = pool.size();
                    pool.push_back({});
                }
                rt = pool[rt].nxt[o];
                ++pool[rt].cnt;
            }
        }
        vector<int> ans;
        for(auto &it: words) {
            int rt = 0, ctr = 0;
            for(char ch: it) {
                int o = ch - 'a';
                rt = pool[rt].nxt[o];
                ctr += pool[rt].cnt;
            }
            ans.push_back(ctr);
        }
        return ans;
    }
};
