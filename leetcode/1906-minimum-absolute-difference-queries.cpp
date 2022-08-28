class Solution {
    static const int maxv = 101;
    vector<bitset<maxv> > seg;
    int segID(int L, int R) {
        return (L + R) | (L < R);
    }
    void segInit(int L, int R, vector<int> &nums) {
        int rt = segID(L, R);
        if(L == R) {
            seg[rt].reset();
            seg[rt].set(nums[L]);
            return;
        }
        int M = (L + R) >> 1;
        int lch = segID(L, M), rch = segID(M + 1, R);
        segInit(L, M, nums);
        segInit(M + 1, R, nums);
        seg[rt] = seg[lch] | seg[rch];
    }
    void segQuery(int L, int R, int l, int r, bitset<maxv> &msk) {
        if(l <= L && R <= r) {
            int rt = segID(L, R);
            msk |= seg[rt];
            return;
        }
        int M = (L + R) >> 1;
        if(l <= M)
            segQuery(L, M, l, r, msk);
        if(r > M)
            segQuery(M + 1, R, l, r, msk);
    }
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        seg.resize(n << 1 | 1);
        segInit(0, n - 1, nums);
        vector<int> ans;
        bitset<maxv> msk;
        for(auto &it: queries) {
            msk.reset();
            segQuery(0, n - 1, it[0], it[1], msk);
            int res = maxv, las = -maxv;
            for(int i = 0; i < maxv; ++i)
                if(msk.test(i)) {
                    res = min(res, i - las);
                    las = i;
                }
            ans.push_back(res < maxv ? res : -1);
        }
        return ans;
    }
};
