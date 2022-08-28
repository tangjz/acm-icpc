class Solution {
public:
    int maxInvestment(vector<int>& product, int limit) {
        int n = product.size();
        sort(product.begin(), product.end(), greater<>());
        product.push_back(0);
        long long ans = 0;
        for(int i = 0; i < n; ++i) {
            int L = product[i + 1], R = product[i], len = R - L;
            int q = limit / (i + 1), r = limit % (i + 1);
            if(q >= len) {
                limit -= len * (i + 1);
                ans += (L + R + 1LL) * len / 2 * (i + 1);
                continue;
            }
            ans += (R - q + 1LL + R) * q / 2 * (i + 1);
            ans += 1LL * (R - q) * r;
            break;
        }
        return ans % ((int)1e9 + 7);
    }
};
