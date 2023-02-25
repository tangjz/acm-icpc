class Solution {
public:
    long long putMarbles(vector<int>& A, int k) {
        typedef long long LL;
        int n = A.size();
        vector<int> seq(n - 1);
        for(int i = 0; i + 1 < n; ++i)
            seq[i] = A[i] + A[i + 1];
        sort(seq.begin(), seq.end());
        LL ans = 0;
        for(int i = 0; i + 1 < k; ++i)
            ans += seq[n - 2 - i] - seq[i];
        return ans;
    }
};
