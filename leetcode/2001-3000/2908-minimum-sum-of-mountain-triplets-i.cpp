class Solution {
public:
    int minimumSum(vector<int>& A) {
        int n = A.size(), ans = INT_MAX;
        vector<int> pre(n);
        pre[0] = INT_MAX;
        for(int i = 1; i < n; ++i)
            pre[i] = min(pre[i - 1], A[i - 1]);
        for(int j = n - 2, suf = INT_MAX; j > 0; --j) {
            suf = min(suf, A[j + 1]);
            if(pre[j] < A[j] && suf < A[j])
                ans = min(ans, pre[j] + A[j] + suf);
        }
        return ans < INT_MAX ? ans : -1;
    }
};
