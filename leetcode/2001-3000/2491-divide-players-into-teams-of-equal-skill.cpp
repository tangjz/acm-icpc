class Solution {
public:
    long long dividePlayers(vector<int>& A) {
        long long ans = 0;
        int n = A.size();
        sort(A.begin(), A.end());
        int sum = A[0] + A[n - 1];
        for(int i = 0, j = n - 1; i < j; ++i, --j) {
            int cur = A[i] + A[j];
            if(sum != cur)
                return -1;
            ans += A[i] * A[j];
        }
        return ans;
    }
};
