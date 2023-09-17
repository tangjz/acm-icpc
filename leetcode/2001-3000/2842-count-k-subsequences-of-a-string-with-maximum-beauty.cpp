class Solution {
public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        typedef long long LL;
        static const int maxc = 26, mod = (int)1e9 + 7;
        static int ctr[maxc + 1], ord[maxc + 1], inv[maxc + 1];
        memset(ctr, 0, sizeof ctr);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        iota(ord, ord + maxc, 0);
        sort(ord, ord + maxc, [&](int const &u, int const &v) {
            return ctr[u] > ctr[v];
        });
        if(k > maxc || !ctr[ord[k - 1]])
            return 0;
        int ans = 1, L = k - 1, R = k - 1;
        for( ; L > 0 && ctr[ord[L - 1]] == ctr[ord[L]]; --L);
        for( ; R + 1 < maxc && ctr[ord[R + 1]] == ctr[ord[R]]; ++R);
        R = R - L + 1;
        L = k - L;
        for(int i = 0; i < k; ++i)
            ans = (LL)ans * ctr[ord[i]] % mod;
        for(int i = 1; i <= L; ++i) {
            inv[i] = i > 1 ? mod - (int)(mod / i * (LL)inv[mod % i] % mod) : 1;
            ans = (LL)ans * (R - i + 1) % mod * inv[i] % mod;
        }
        return ans;
    }
};
