class Solution {
public:
    int unequalTriplets(vector<int>& A) {
        int n = A.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                for(int k = j + 1; k < n; ++k)
                    ans += A[i] != A[j] && A[j] != A[k] && A[i] != A[k];
        return ans;
    }
};
