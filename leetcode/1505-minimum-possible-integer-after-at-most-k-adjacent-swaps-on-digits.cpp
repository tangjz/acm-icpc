class Solution {
    static const int maxd = 10;
    struct Segment {
        pair<int, int> val;
        int cnt;
        void upd(pair<int, int> v) {
            val = v;
            cnt = v.first < maxd;
        }
        void upd(Segment &lft, Segment &rht) {
            val = min(lft.val, rht.val);
            cnt = lft.cnt + rht.cnt;
        }
    };
    vector<Segment> seg;
    int seg_idx(int L, int R) {
        return (L + R) | (L < R);
    }
    void seg_init(int L, int R, string &num) {
        int rt = seg_idx(L, R);
        if(L == R) {
            seg[rt].upd({(int)(num[L] - '0'), L});
        } else {
            int M = (L + R) >> 1;
            int lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
            seg_init(L, M, num);
            seg_init(M + 1, R, num);
            seg[rt].upd(seg[lch], seg[rch]);
        }
    }
    int seg_get(int L, int R, int x) {
        int rt = seg_idx(L, R), ret = 0;
        if(L == R) {
            int tmp = maxd;
            seg[rt].upd({tmp, x});
        } else {
            int M = (L + R) >> 1;
            int lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
            if(x <= M) {
                ret += seg_get(L, M, x);
            } else {
                ret += seg[lch].cnt;
                ret += seg_get(M + 1, R, x);
            }
            seg[rt].upd(seg[lch], seg[rch]);
        }
        return ret;
    }
    pair<int, int> seg_que(int L, int R, int x) {
        int rt = seg_idx(L, R);
        if(seg[rt].cnt <= x)
            return seg[rt].val;
        int M = (L + R) >> 1;
        int lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
        if(seg[lch].cnt >= x)
            return seg_que(L, M, x);
        return min(seg[lch].val, seg_que(M + 1, R, x - seg[lch].cnt));
    }
public:
    string minInteger(string num, int k) {
        int n = (int)num.size();
        seg.resize(n << 1 | 1);
        seg_init(0, n - 1, num);
        string ret = "";
        for(int i = 0; i < n; ++i) {
            pair<int, int> best = seg_que(0, n - 1, k + 1);
            ret += '0' + best.first;
            int cost = seg_get(0, n - 1, best.second);
            k -= cost;
        }
        return ret;
    }
};
