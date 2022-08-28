class MajorityChecker {
    int n;
    unordered_map<int, vector<int> > pos;
    int pos_cnt(int x, int L, int R) {
        auto it = pos.find(x);
        if(it == pos.end())
            return 0;
        auto &vec = it -> second;
        if(R < vec.front() || L > vec.back())
            return 0;
        auto pR = upper_bound(vec.begin(), vec.end(), R);
        auto pL = lower_bound(vec.begin(), vec.end(), L);
        return pR - pL;
    }
    vector<pair<int, int> > seg;
    int seg_idx(int L, int R) {
        return (L + R) | (L < R);
    }
    void seg_up(pair<int, int> &rt, pair<int, int> const &lft, pair<int, int> const &rht) {
        if(lft.second < rht.second)
            seg_up(rt, rht, lft);
        else
            rt = {lft.first, lft.first == rht.first ? lft.second + rht.second : lft.second - rht.second};
    }
    int seg_init(int L, int R, vector<int> &arr) {
        int rt = seg_idx(L, R);
        if(L < R) {
            int M = (L + R) >> 1;
            int lch = seg_init(L, M, arr);
            int rch = seg_init(M + 1, R, arr);
            seg_up(seg[rt], seg[lch], seg[rch]);
        } else {
            seg[rt] = {arr[L], 1};
        }
        return rt;
    }
    pair<int, int> seg_que(int L, int R, int l, int r) {
        if(l <= L && R <= r)
            return seg[seg_idx(L, R)];
        int M = (L + R) >> 1;
        pair<int, int> ret = {};
        if(l <= M)
            seg_up(ret, ret, seg_que(L, M, l, r));
        if(r > M)
            seg_up(ret, ret, seg_que(M + 1, R, l, r));
        return ret;
    }
public:
    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        seg.clear();
        seg.resize(n + n + 1);
        seg_init(0, n - 1, arr);
        for(int i = 0; i < n; ++i)
            pos[arr[i]].push_back(i);
    }
    
    int query(int left, int right, int threshold) {
        pair<int, int> ans = seg_que(0, n - 1, left, right);
        // printf("%d %d %d\n", ans.first, ans.second, pos_cnt(ans.first, left, right));
        if(ans.second > 0 && pos_cnt(ans.first, left, right) >= threshold)
            return ans.first;
        return -1;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
