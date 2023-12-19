class Solution {
public:
    long long countSubarrays(vector<int>& A, int k) {
        typedef long long LL;
        int n = A.size(), upp = 0;
        vector<int> pos;
        for(int i = 0; i < n; ++i) {
            if(A[i] < upp)
                continue;
            if(A[i] > upp) {
                upp = A[i];
                pos.clear();
            }
            pos.push_back(i);
        }
        int m = pos.size();
        LL ans = 0;
        for(int i = k - 1; i < m; ++i) {
            int M = pos[i - k + 1], L = i > k - 1 ? pos[i - k] : -1;
            ans += (LL)(M - L) * (n - pos[i]);
        }
        return ans;
    }
};
