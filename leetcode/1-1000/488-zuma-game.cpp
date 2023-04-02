class Solution {
    typedef long long LL;
    // pat: [0:5) shuffled "RYBGW"
    // seq (63 bits): [3k+5:3k+8) board[k]
    // ctr (45 bits): [3k:3k+3) hand for pat[k], [5k+15:5k+20) board for pat[k], [40:45) len
    struct State {
        LL seq, ctr;
        bool operator < (State const &t) const {
            // rule: distinguishable
            if(seq != t.seq)
                return seq < t.seq;
            return ctr < t.ctr;
        }
        bool operator == (State const &t) const {
            return seq == t.seq && ctr == t.ctr;
        }
    };
    struct StateHash {
        size_t operator ()(State const &t) const {
            return t.seq ^ t.ctr;
        }
    };
    struct Node {
        State state;
        int dep, val;
        bool operator < (Node const &t) const {
            // rule: the greater is better
            if(val != t.val)
                return val > t.val;
            if(dep != t.dep)
                return dep < t.dep;
            return state < t.state;
        }
    };
public:
    int findMinStep(string board, string hand) {
        static mt19937_64 rnd(19260817);
        string pat = "RYBGW";
        shuffle(pat.begin(), pat.end(), rnd);
       
        int n = board.size(), m = hand.size();
        State s = {};
        s.ctr |= (LL)n << 40;
        for(int i = 0, u = 0; i < n; ++i, u += 3)
            for(int k = 0; k < 5; ++k)
                if(pat[k] == board[i]) {
                    s.seq |= (LL)k << u;
                    break;
                }
        for(int i = 0, u = 0, v = 15; i < 5; ++i, u += 3, v += 5) {
            int c0 = 0, c1 = 0;
            for(int k = 0; k < m; ++k)
                c0 += pat[i] == hand[k];
            for(int k = 0; k < n; ++k)
                c1 += pat[i] == board[k];
            s.ctr |= (LL)c0 << u | (LL)c1 << v;
        }

        unordered_map<State, int, StateHash> hs;
        priority_queue<Node> pq;
        auto upd = [&](State &cs, int dep) {
            int adt = 0;
            for(int i = 0, u = 0, v = 15; i < 5; ++i, u += 3, v += 5) {
                int remH = (cs.ctr >> u) & 7, remB = (cs.ctr >> v) & 31;
                if(!remB)
                    continue;
                if(remH + remB < 3)
                    return;
                adt += max(3 - remB, 0);
            }
            auto it = hs.find(cs);
            if(it != hs.end() && it -> second <= dep)
                return;
            hs[cs] = dep;
            pq.push({cs, dep, dep + adt});
        };
        upd(s, 0);
        vector<int> seq(n + m);
        while(!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            State cs = cur.state, ns;
            int n = (cs.ctr >> 40) & 31;
            for(int i = 0, u = 0; i < n; ++i, u += 3)
                seq[i] = (cs.seq >> u) & 7;
            for(int i = 0, u = 0, v = 15; i < 5; ++i, u += 3, v += 5) {
                int remH = (cs.ctr >> u) & 7, remB = (cs.ctr >> v) & 31;
                if(!remH || remH + remB < 3)
                    continue;
                for(int j = 0; j <= n; ++j) {
                    // seq[0:j) + i + seq[j:n)
                    if(j > 0 && j < n && seq[j - 1] == seq[j] && seq[j] == i)
                        continue;
                    if(j > 0 && j < n && seq[j - 1] != seq[j] && seq[j - 1] != i && seq[j] != i) // best improvement
                        continue;
                    int L = j, R = j;
                    bool fir = 1;
                    ns = cs;
                    while(true) {
                        int k = -1, cnt = 0, qL = L, qR = R;
                        if(fir) {
                            k = i;
                            ++cnt;
                        } else if(L > 0 && R < n && seq[L - 1] == seq[R]) {
                            k = seq[R];
                        }
                        for( ; qL > 0 && seq[qL - 1] == k; --qL, ++cnt);
                        for( ; qR < n && seq[qR] == k; ++qR, ++cnt);
                        if(cnt < 3)
                            break;
                        if(fir) {
                            --cnt;
                            ns.ctr -= 1LL << (3 * k);
                            fir = 0;
                        }
                        ns.ctr -= (LL)cnt << (15 + 5 * k);
                        L = qL;
                        R = qR;
                    }
                    if(fir) {
                        // seq[0:j) + i + seq[j:n)
                        ns.ctr += 1LL << 40;
                        L = L * 3;
                        ns.seq = (ns.seq & ((1LL << L) - 1)) | (LL)i << L | ((ns.seq >> L) << (L + 3));
                        ns.ctr -= 1LL << u;
                        ns.ctr += 1LL << v;
                    } else {
                        // seq[0:L) + seq[R:n)
                        ns.ctr -= (LL)(R - L) << 40;
                        L = L * 3;
                        R = R * 3;
                        ns.seq = (ns.seq & ((1LL << L) - 1)) | ((ns.seq >> R) << L);
                    }
                    if(!((ns.ctr >> 40) & 31))
                        return cur.dep + 1;
                    upd(ns, cur.dep + 1);
                }
            }
        }
        return -1;
    }
};
