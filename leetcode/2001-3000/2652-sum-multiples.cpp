class Solution {
public:
    int sumOfMultiples(int n) {
        const int m = 3, seq[m] = {3, 5, 7};
        int ans = 0;
        for(int i = 1; i < (1 << m); ++i) {
            int sgn = -1, val = n, prd = 1;
            for(int j = 0; val && j < m; ++j)
                if((i >> j) & 1) {
                    sgn = -sgn;
                    val /= seq[j];
                    prd *= seq[j];
                }
            if(!val)
                continue;
            ans += sgn * prd * (val * (val + 1) / 2);
        }
        return ans;
    }
};
