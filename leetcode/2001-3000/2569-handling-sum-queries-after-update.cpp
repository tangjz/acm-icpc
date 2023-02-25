class Solution {
    struct Node {
        int tot, cnt;
        bool rev;
        void flip() {
            cnt = tot - cnt;
            rev = !rev;
        }
    };
    vector<Node> seg;
    int segIdx(int L, int R) {
        return (L + R) | (L < R);
    }
    int segInit(int L, int R, vector<int> &nums1) {
        int rt = segIdx(L, R);
        seg[rt] = (Node){R - L + 1, 0, 0};
        if(L < R) {
            int M = (L + R) >> 1;
            seg[rt].cnt = seg[segInit(L, M, nums1)].cnt + seg[segInit(M + 1, R, nums1)].cnt;
        } else {
            seg[rt].cnt = nums1[L];
        }
        return rt;
    }
    void segUp(Node &rt, Node &lch, Node &rch) {
        rt.cnt = lch.cnt + rch.cnt;
    }
    void segDown(Node &rt, Node &lch, Node &rch) {
        if(!rt.rev)
            return;
        lch.flip();
        rch.flip();
        rt.rev = 0;
    }
    void segUpd(int L, int R, int l, int r) {
        int rt = segIdx(L, R);
        if(l <= L && R <= r) {
            seg[rt].flip();
            return;
        }
        int M = (L + R) >> 1, lch = segIdx(L, M), rch = segIdx(M + 1, R);
        segDown(seg[rt], seg[lch], seg[rch]);
        if(l <= M)
            segUpd(L, M, l, r);
        if(r > M)
            segUpd(M + 1, R, l, r);
        segUp(seg[rt], seg[lch], seg[rch]);
    }
    int segQue(int L, int R, int l, int r) {
        if(l <= L && R <= r)
            return seg[segIdx(L, R)].cnt;
        int M = (L + R) >> 1, ret = 0;
        if(l <= M)
            ret += segQue(L, M, l, r);
        if(r > M)
            ret += segQue(M + 1, R, l, r);
        return ret;
    }
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        typedef long long LL;
        int n = nums1.size();
        seg.resize(n + n + 1);
        segInit(0, n - 1, nums1);
        LL ans = 0;
        for(int x: nums2)
            ans += x;
        vector<LL> ret;
        for(auto &it: queries) {
            if(it[0] == 1) {
                segUpd(0, n - 1, it[1], it[2]);
            } else if(it[0] == 2) {
                ans += (LL)it[1] * seg[segIdx(0, n - 1)].cnt;
            } else {
                ret.push_back(ans);
            }
        }
        return ret;
    }
};
