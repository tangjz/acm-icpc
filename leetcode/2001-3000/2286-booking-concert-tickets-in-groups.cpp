class BookMyShow {
    typedef long long LL;
    int n, m;
    struct Node {
        int upp;
        LL sum;
    };
    vector<Node> seg;
    int segIdx(int L, int R) {
        return (L + R) | (L < R);
    }
    void segUp(Node &rt, Node const &lft, Node const &rht) {
        rt.upp = max(lft.upp, rht.upp);
        rt.sum = lft.sum + rht.sum;
    }
    int segInit(int L, int R) {
        int rt = segIdx(L, R);
        if(L < R) {
            int M = (L + R) >> 1;
            int lch = segInit(L, M), rch = segInit(M + 1, R);
            segUp(seg[rt], seg[lch], seg[rch]);
        } else {
            seg[rt].upp = seg[rt].sum = m;
        }
        return rt;
    }
    Node segQue(int L, int R, int l, int r) {
        if(l <= L && R <= r)
            return seg[segIdx(L, R)];
        int M = (L + R) >> 1;
        if(r <= M)
            return segQue(L, M, l, r);
        if(l > M)
            return segQue(M + 1, R, l, r);
        Node ret;
        segUp(ret, segQue(L, M, l, r), segQue(M + 1, R, l, r));
        return ret;
    }
    int segFind(int L, int R, int k) {
        while(L < R) {
            int M = (L + R) >> 1;
            if(seg[segIdx(L, M)].upp < k) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
    void segDec(int L, int R, int l, int r, int &k) {
        int rt = segIdx(L, R);
        if(!seg[rt].sum || !k)
            return;
        if(L == R) {
            int com = min(seg[rt].upp, k);
            seg[rt].upp -= com;
            seg[rt].sum -= com;
            k -= com;
            return;
        }
        int M = (L + R) >> 1;
        if(l <= M)
            segDec(L, M, l, r, k);
        if(r > M)
            segDec(M + 1, R, l, r, k);
        segUp(seg[rt], seg[segIdx(L, M)], seg[segIdx(M + 1, R)]);
    }
public:
    BookMyShow(int n, int m) {
        this -> n = n;
        this -> m = m;
        seg.resize(n << 1);
        segInit(0, n - 1);
    }
    
    vector<int> gather(int k, int maxRow) {
        Node ret = segQue(0, n - 1, 0, maxRow);
        if(ret.upp < k)
            return {};
        int pos = segFind(0, n - 1, k), rem = seg[segIdx(pos, pos)].upp;
        segDec(0, n - 1, pos, pos, k);
        return {pos, m - rem};
    }
    
    bool scatter(int k, int maxRow) {
        Node ret = segQue(0, n - 1, 0, maxRow);
        if(ret.sum < k)
            return false;
        segDec(0, n - 1, 0, maxRow, k);
        assert(!k);
        return 1;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */
