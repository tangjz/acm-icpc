class Solution {
    vector<int> seg;
    int segIdx(int L, int R) {
        return (L + R) | (L < R);
    }
    void segInit(int L, int R) {
        seg[segIdx(L, R)] = 0;
        if(L < R) {
            int M = (L + R) >> 1;
            segInit(L, M);
            segInit(M + 1, R);
        }
    }
    void segUpd(int L, int R, int x, int v) {
        int rt = segIdx(L, R);
        if(L == R) {
            seg[rt] = v;
            return;
        }
        int M = (L + R) >> 1;
        if(x <= M)
            segUpd(L, M, x, v);
        else
            segUpd(M + 1, R, x, v);
        seg[rt] = max(seg[segIdx(L, M)], seg[segIdx(M + 1, R)]);
    }
    int segQue(int L, int R, int l, int r) {
        if(l <= L && R <= r)
            return seg[segIdx(L, R)];
        int M = (L + R) >> 1, ret = 0;
        if(l <= M)
            ret = max(ret, segQue(L, M, l, r));
        if(r > M)
            ret = max(ret, segQue(M + 1, R, l, r));
        return ret;
    }
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> que = nums;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        seg.resize(m + m + 1);
        segInit(0, m - 1);
        for(int x: nums) {
            int u = lower_bound(que.begin(), que.end(), x) - que.begin();
            int v = lower_bound(que.begin(), que.end(), x - k) - que.begin();
            segUpd(0, m - 1, u, (v < u ? segQue(0, m - 1, v, u - 1) : 0) + 1);
        }
        return segQue(0, m - 1, 0, m - 1);
    }
};
