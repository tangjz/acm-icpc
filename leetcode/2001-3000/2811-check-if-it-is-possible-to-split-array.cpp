class Solution {
public:
    bool canSplitArray(vector<int>& A, int m) {
        int n = A.size();
        if(n <= 2)
            return 1;
        for(int i = 1; i < n; ++i)
            if(A[i - 1] + A[i] >= m)
                return 1;
        return 0;
    }
};
