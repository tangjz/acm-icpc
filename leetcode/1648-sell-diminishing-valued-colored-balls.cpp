class Solution {
public:
    int maxProfit(vector<int>& seq, int tot) {
        typedef long long LL;
        LL ans = 0;
        seq.push_back(0);
        sort(seq.begin(), seq.end());
        int n = seq.size();
        for(int i = n - 1; tot > 0 && i > 0; --i) {
            int mul = n - i, adt = min(tot / mul, seq[i] - seq[i - 1]);
            ans += (seq[i] - adt + 1LL + seq[i]) * adt / 2 * mul;
            tot -= mul * adt;
            if(seq[i] - seq[i - 1] > adt) {
                ans += (LL)(seq[i] - adt) * tot;
                tot = 0;
            }
        }
        return ans % ((int)1e9 + 7);
    }
};
