class StreamChecker {
    static const int maxc = 26, maxm = 1 << 13 | 1;
    typedef struct {
        bool suf;
        int cnt, sta, msk, nxt;
    } Trie;
    vector<Trie> nodes;
    vector<int> bcnt;
    int cur;

    void parse(vector<string> &words) {
        int n = words.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        queue<vector<int> > que;
        nodes = {};
        que.push({(int)nodes.size(), 0, 0, n}); // id, dep, L, R
        nodes.push_back((Trie){});
        vector<vector<int> > cand(maxc);
        while(!que.empty()) {
            auto &it = que.front();
            int id = it[0], dep = it[1], L = it[2], R = it[3];
            que.pop();
            nodes[id].sta = nodes.size();
            for(int i = L; i < R; ++i) {
                int j = ord[i];
                if(dep >= words[j].size()) {
                    nodes[id].suf = true;
                    continue;
                }
                int k = words[j][dep] - 'a';
                if(!((nodes[id].msk >> k) & 1)) {
                    ++nodes[id].cnt;
                    nodes[id].msk |= 1 << k;
                    cand[k].clear();
                }
                cand[k].push_back(j);
            }
            if(nodes[id].cnt) {
                for(int i = 0; i < maxc; ++i) {
                    if(!((nodes[id].msk >> i) & 1))
                        continue;
                    int pL = L;
                    for(int x: cand[i]) {
                        ord[L++] = x;
                    }
                    que.push({(int)nodes.size(), dep + 1, pL, L});
                    nodes.push_back((Trie){}); // warn!
                }
            }
        }
    }

    void build() {
        if(!nodes[0].cnt) {
            return;
        }
        queue<int> que;
        Trie &cur = nodes[0];
        int pos = cur.sta;
        for(int i = 0; i < maxc; ++i) {
            if(!((cur.msk >> i) & 1))
                continue;
            nodes[pos].suf |= nodes[0].suf;
            que.push(pos++);
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            Trie &cur = nodes[u];
            int pos = cur.sta;
            for(int i = 0; i < maxc; ++i) {
                if(!((cur.msk >> i) & 1))
                    continue;
                Trie &sub = nodes[pos];
                que.push(pos++);
                for(sub.nxt = cur.nxt; sub.nxt && !((nodes[sub.nxt].msk >> i) & 1); sub.nxt = nodes[sub.nxt].nxt);
                if((nodes[sub.nxt].msk >> i) & 1) {
                    int msk = nodes[sub.nxt].msk & ((1 << i) - 1);
                    sub.nxt = nodes[sub.nxt].sta + bcnt[msk & (maxm - 2)] + bcnt[msk >> (maxc >> 1)];
                }
                sub.suf |= nodes[sub.nxt].suf;
            }
        }
    }

public:
    StreamChecker(vector<string>& words) {
        bcnt.resize(maxm);
        bcnt[0] = 0;
        for(int i = 1; i < maxm; ++i)
            bcnt[i] = bcnt[i >> 1] + (i & 1);
        parse(words);
        build();
        cur = 0;
    }

    bool query(char letter) {
        int k = letter - 'a';
        for( ; cur && !((nodes[cur].msk >> k) & 1); cur = nodes[cur].nxt);
        if((nodes[cur].msk >> k) & 1) {
            int msk = nodes[cur].msk & ((1 << k) - 1);
            cur = nodes[cur].sta + bcnt[msk & (maxm - 2)] + bcnt[msk >> (maxc >> 1)];
        }
        return nodes[cur].suf;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
