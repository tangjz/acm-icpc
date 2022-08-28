class Solution {
    vector<int> d;
    int binom(int n, int m) {
        if(n < m || m < 0)
            return 0;
        int ans = 1;
        vector<int> ctr(n + 1);
        for(int i = n; i >= 2; --i) {
            ctr[i] += 1 - (i <= m) - (i <= n - m);
            int j = d[i];
            if(j < i) {
                ctr[j] += ctr[i];
                ctr[i / j] += ctr[i];
            } else {
                for(int x = i, k = ctr[i]; k > 0; x *= x, k >>= 1)
                    if(k & 1)
                        ans *= x;
            }
        }
        return ans;
    }
public:
    Solution() {
        const int maxn = 199;
        vector<int>(maxn).swap(d);
        vector<int> pr;
        for(int i = 2; i < maxn; ++i) {
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p : pr) {
                int j = i * p;
                if(j >= maxn)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
    }
    int uniquePaths(int m, int n) {
        return binom(n + m - 2, n - 1);
    }
};
