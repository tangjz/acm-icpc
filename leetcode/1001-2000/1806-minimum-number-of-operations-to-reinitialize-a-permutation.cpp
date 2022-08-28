class Solution {
public:
    int reinitializePermutation(int n) {
        vector<int> perm(n);
        for(int i = 0; i < n; ++i)
            perm[i] = ((i & 1) * n + i) >> 1;
        int ans = 1;
        for(int i = 0; i < n; ++i) {
            if(perm[i] == -1)
                continue;
            int cnt = 0;
            for(int j = i; perm[j] != -1; ++cnt) {
                // printf("%d: %d\n", j, perm[j]);
                int k = perm[j];
                perm[j] = -1;
                j = k;
            }
            // printf("%d\n", cnt);
            ans *= cnt / gcd(ans, cnt);
        }
        return ans;
    }
};
