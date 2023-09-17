class Solution {
    struct Node {
        int low, cnt;
        void upd(Node &lft, Node &rht) {
            low = min(lft.low, rht.low);
            cnt = (low == lft.low ? lft.cnt : 0) + (low == rht.low ? rht.cnt : 0);
        }
    };
    int segIdx(int L, int R) {
        return (L + R) | (L < R);
    }
    int segInit(vector<Node> &seg, int L, int R) {
        int rt = segIdx(L, R);
        if(L == R) {
            seg[rt] = (Node){0, 1};
        } else {
            int M = (L + R) >> 1;
            int lch = segInit(seg, L, M);
            int rch = segInit(seg, M + 1, R);
            seg[rt].upd(seg[lch], seg[rch]);
        }
        return rt;
    }
    void segUpd(vector<Node> &seg, int L, int R, int x, int v) {
        int rt = segIdx(L, R);
        if(L == R) {
            seg[rt].low += v;
        } else {
            int M = (L + R) >> 1;
            if(x <= M)
                segUpd(seg, L, M, x, v);
            else
                segUpd(seg, M + 1, R, x, v);
            int lch = segIdx(L, M);
            int rch = segIdx(M + 1, R);
            seg[rt].upd(seg[lch], seg[rch]);
        }
    }
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<int> ans(m);
        vector<vector<int> > eve;
        for(auto &it: logs) {
            eve.push_back({it[1], 0, it[0]});
            eve.push_back({it[1] + x, 2, it[0]});
        }
        for(int i = 0; i < m; ++i)
            eve.push_back({queries[i], 1, i});
        sort(eve.begin(), eve.end());
        vector<Node> seg(n + n + 1);
        segInit(seg, 1, n);
        for(auto &it: eve) {
            if(it[1] == 1) {
                Node &rt = seg[segIdx(1, n)];
                ans[it[2]] = rt.low ? 0 : rt.cnt;
            } else {
                segUpd(seg, 1, n, it[2], it[1] ? -1 : 1);
            }
        }
        return ans;
    }
};
