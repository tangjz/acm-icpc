class Solution {
public:
    int sumIndicesWithKSetBits(vector<int>& A, int k) {
        int n = A.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            if(__builtin_popcount(i) == k)
                ans += A[i];
        return ans;
    }
};
