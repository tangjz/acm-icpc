class Solution {
public:
    int longestEqualSubarray(vector<int>& A, int k) {
        int n = A.size(), ans = 0;
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return A[u] < A[v] || (A[u] == A[v] && u < v);
        });
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && A[ord[i]] == A[ord[j]]; ++j);
            for(int L = i, R = i; L < j; ++L) {
                for( ; R < j && ord[R] - ord[L] <= R - L + k; ++R);
                ans = max(ans, R - L);
            }
        }
        return ans;
    }
};
