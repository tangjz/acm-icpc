class Solution {
public:
    int countPairs(vector<int>& A, int upp) {
        int n = A.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                ans += A[i] + A[j] < upp;
        return ans;
    }
};
