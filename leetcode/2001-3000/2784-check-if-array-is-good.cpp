class Solution {
public:
    bool isGood(vector<int>& A) {
        int n = A.size();
        if(n == 1)
            return false;
        sort(A.begin(), A.end());
        bool good = A[n - 2] == A[n - 1] && A[n - 1] == n - 1;
        for(int i = 0; good && i < n - 2; ++i)
            good &= A[i] == i + 1;
        return good;
    }
};
