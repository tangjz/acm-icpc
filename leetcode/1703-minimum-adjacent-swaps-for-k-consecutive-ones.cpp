class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        typedef long long LL;
        int n = 0, m = 0;
        vector<LL> psum;
        psum.push_back(0);
        for(int x : nums) {
            if(x > 0) {
                psum.push_back(psum.back() + (n - m));
                ++m;
            }
            ++n;
        }
        LL ans = LLONG_MAX;
        for(int L = 1, R = k; R <= m; ++L, ++R) {
            int M = (L + R) >> 1;
            LL pos = psum[M] - psum[M - 1];
            ans = min(ans, (M - L + 1 - (R - M)) * pos + (psum[R] - psum[M] - (psum[M] - psum[L - 1])));
        }
        return ans;
    }
};
