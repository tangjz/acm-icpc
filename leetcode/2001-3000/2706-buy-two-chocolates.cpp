class Solution {
public:
    int buyChoco(vector<int>& A, int upp) {
        int ans = -1, n = A.size();
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                ans = max(ans, upp - A[i] - A[j]);
        return ans < 0 ? upp : ans;
    }
};
