class Solution {
public:
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size();
        k = gcd(k, n);
        int m = n / k;
        vector<int> seq(m);
        long long ans = 0;
        for(int i = 0; i < k; ++i) {
            for(int p = 0, q = i; q < n; ++p, q += k)
                seq[p] = arr[q];
            sort(seq.begin(), seq.end());
            int mid = seq[(m - 1) / 2];
            for(int p = 0; p < m; ++p)
                ans += abs(seq[p] - mid);
        }
        return ans;
    }
};
