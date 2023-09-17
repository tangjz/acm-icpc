class Solution {
public:
    int findValueOfPartition(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        int ans = A[1] - A[0];
        for(int i = 2; i < n; ++i)
            ans = min(ans, A[i] - A[i - 1]);
        return ans;
    }
};
