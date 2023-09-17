#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e4 + 1, maxd = 31, tr[2][2] = {
    {1, 1},
    {1, 0},
};

int n, d, q;

struct Node {
    int nxt[2];
    void init(int x) {
        nxt[0] = nxt[1] = 0;
        for(int i = 0, o; i < d; ++i, x >>= 1) {
            o = x & 1;
            nxt[0] |= tr[0][o] << i;
            nxt[1] |= tr[1][o] << i;
        }
    }
    void merge(Node &lft, Node &rht) {
        nxt[0] = nxt[1] = 0;
        for(int i = 0, o; i < d; ++i) {
            o = (lft.nxt[0] >> i) & 1;
            nxt[0] |= rht.nxt[o] & (1 << i);
            o = (lft.nxt[1] >> i) & 1;
            nxt[1] |= rht.nxt[o] & (1 << i);
        }
    }
} seg[maxn << 1 | 1];

inline int segIdx(int L, int R) {
    return (L + R) | (L < R);
}

int segInit(int L, int R, vector<int> &seq) {
    int rt = segIdx(L, R);
    if(L == R) {
        seg[rt].init(seq[L]);
    } else {
        int M = (L + R) >> 1;
        int lch = segInit(L, M, seq), rch = segInit(M + 1, R, seq);
        seg[rt].merge(seg[lch], seg[rch]);
    }
    return rt;
}

void segUpd(int L, int R, int x, int v) {
    int rt = segIdx(L, R);
    if(L == R) {
        seg[rt].init(v);
        return;
    }
    int M = (L + R) >> 1;
    int lch = segIdx(L, M), rch = segIdx(M + 1, R);
    if(x <= M)
        segUpd(L, M, x, v);
    else
        segUpd(M + 1, R, x, v);
    seg[rt].merge(seg[lch], seg[rch]);
}

class Solution {
public:
    int getNandResult(int k, vector<int>& arr, vector<vector<int>>& operations) {
        int ans = 0;
        n = arr.size();
        d = k;
        q = operations.size();
        segInit(0, n - 1, arr);
        for(auto &it: operations) {
            int &typ = it[0], &x = it[1], &y = it[2];
            if(!typ) {
                segUpd(0, n - 1, x, y);
                continue;
            }
            Node &cur = seg[segIdx(0, n - 1)];
            int res = 0;
            for(int i = 0; i < d; ++i, y >>= 1) {
                static int seq[3], vis[3] = {};
                vis[0] = vis[1] = -1;
                seq[0] = y & 1;
                vis[seq[0]] = 0;
                for(int j = 1; j < 3; ++j) {
                    seq[j] = (cur.nxt[seq[j - 1]] >> i) & 1;
                    if(vis[seq[j]] != -1) {
                        int o = seq[j], sta = vis[o], per = j - vis[o];
                        int xx = x < sta ? x : (x - sta) % per + sta;
                        res |= seq[xx] << i;
                        break;
                    }
                    vis[seq[j]] = j;
                }
            }
            ans ^= res;
        }
        return ans;
    }
};
