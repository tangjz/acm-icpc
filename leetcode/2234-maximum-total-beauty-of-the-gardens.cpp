class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        typedef long long LL;
        int n = flowers.size();
        LL ans = 0;
        sort(flowers.begin(), flowers.end());
        vector<LL> psum = {0LL};
        for(int x: flowers)
            psum.push_back(psum.back() + x);
        int cnt = 0;
        for( ; cnt < n && flowers[n - 1 - cnt] >= target; ++cnt);
        for(int i = cnt; i <= n; ++i) {
            // flowers[:n-i]
            int L = 0, R = n - i - 1;
            while(L < R) {
                int M = (L + R + 1) >> 1;
                if(newFlowers < (M + 1LL) * flowers[M] - psum[M + 1]) {
                    R = M - 1;
                } else {
                    L = M;
                }
            }
            LL rem = newFlowers - ((L + 1LL) * flowers[L] - psum[L + 1]);
            if(rem >= 0) {
                LL val = min(flowers[L] + rem / (L + 1), target - 1LL);
                ans = max(ans, (LL)full * i + (i < n ? (LL)partial * val : 0));
            }
            if(i < n)
                newFlowers -= max(target - flowers[n - 1 - i], 0);
        }
        return ans;
    }
};
