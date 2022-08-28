class Solution {
    static const int maxd = 2, maxe = 30;
    struct TrieNode {
        TrieNode *nxt[maxd];
        TrieNode() {
            memset(nxt, 0, sizeof nxt);
        }
    };
    struct Trie {
        TrieNode *root;
        Trie() : root(new TrieNode()) {}
        ~Trie() {
            freeTrie(root);
        }
        void freeTrie(TrieNode *root) {
            if(root == NULL)
                return;
            for(int i = 0; i < maxd; ++i)
                freeTrie(root -> nxt[i]);
            delete root;
        }
        void insert(int x) {
            TrieNode *cur = root;
            for(int i = maxe - 1; i >= 0; --i) {
                int o = (x >> i) & 1;
                if(cur -> nxt[o] == NULL)
                    cur -> nxt[o] = new TrieNode();
                cur = cur -> nxt[o];
            }
        }
        int match(int x) {
            int ret = 0;
            TrieNode *cur = root;
            for(int i = maxe - 1; i >= 0; --i) {
                int o = (x >> i) & 1;
                if(cur -> nxt[!o] == NULL) {
                    cur = cur -> nxt[o];
                    continue;
                }
                cur = cur -> nxt[!o];
                ret |= 1 << i;
            }
            return ret;
        }
    };
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        int q = (int)queries.size();
        vector<int> ord(q), ans(q, -1);
        sort(nums.begin(), nums.end());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return queries[u][1] < queries[v][1];
        });
        Trie tr;
        auto it = nums.begin();
        for(int idx : ord) {
            auto const &jt = queries[idx];
            while(it != nums.end() && *it <= jt[1])
                tr.insert(*(it++));
            if(it == nums.begin())
                continue;
            ans[idx] = tr.match(jt[0]);
        }
        return ans;
    }
};
