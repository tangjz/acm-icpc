class Solution {
    static const int maxc = 26, maxd = 4;
    struct TrieNode {
        vector<int> idx;
        TrieNode *nxt[maxc + 1];
        TrieNode() : idx() {
            memset(nxt, 0, sizeof nxt);
        }
    } *root, *cand[maxd + 1][maxd + 1];

public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        root = new TrieNode();
        int n = words.size(), m = words[0].size();
        for(int i = 0; i < n; ++i) {
            TrieNode *cur = root;
            cur -> idx.push_back(i);
            for(char &ch : words[i]) {
                int o = ch - 'a';
                if(cur -> nxt[o] == nullptr)
                    cur -> nxt[o] = new TrieNode();
                cur = cur -> nxt[o];
                cur -> idx.push_back(i);
            }
        }
        for(int i = 0; i < m; ++i)
            cand[0][i] = root;
        vector<string> path;
        vector<vector<string> > ret;
        function<void(int)> dfs = [&](int dep) {
            if(dep == m) {
                ret.push_back(path);
                return;
            }
            for(int u: cand[dep][dep] -> idx) {
                bool skip = 0;
                for(int i = 0; i < m; ++i) {
                    int o = words[u][i] - 'a';
                    cand[dep + 1][i] = cand[dep][i] -> nxt[o];
                    skip |= cand[dep + 1][i] == nullptr;
                }
                if(skip)
                    continue;
                path.push_back(words[u]);
                dfs(dep + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return ret;
    }
};
