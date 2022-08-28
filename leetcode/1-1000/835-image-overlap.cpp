class Solution {
    int countBits(unsigned int x) {
        static const int maxd = 15, MSK = (1 << maxd) - 1;
        static unsigned int bits[MSK + 2] = {}, &mx = bits[MSK + 1];
        int ret = 0;
        while(x > 0) {
            size_t y = x & MSK;
            x >>= maxd;
            while(mx < y) {
                ++mx;
                bits[mx] = bits[mx >> 1] + (mx & 1);
            }
            ret += bits[y];
        }
        return ret;
    }
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        const int n = (int)A.size(), MSK = (1 << n) - 1;
        vector<int> a, b;
        a.reserve(n);
        b.reserve(n);
        for(int i = 0; i < n; ++i) {
            int msk = 0;
            for(auto it = A[i].rbegin(); it != A[i].rend(); ++it)
                msk = (msk << 1) | *it;
            a.push_back(msk);
            msk = 0;
            for(auto it = B[i].rbegin(); it != B[i].rend(); ++it)
                msk = (msk << 1) | *it;
            b.push_back(msk);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if((n - i) * (n - j) <= ans)
                    continue;
                int tmp[4] = {};
                for(int k = i; k < n; ++k) {
                    tmp[0] += countBits(a[k - i] & (b[k] >> j));
                    tmp[1] += countBits((a[k] >> j) & b[k - i]);
                    tmp[2] += countBits((a[k - i] >> j) & b[k]);
                    tmp[3] += countBits(a[k] & (b[k - i] >> j));
                }
                ans = max(ans, *max_element(tmp, tmp + 4));
            }
        return ans;
    }
};

static auto fastio = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return nullptr;
}();
