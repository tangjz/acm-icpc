class Solution {
public:
    vector<int> findArray(vector<int>& A) {
        int n = A.size();
        for(int i = n - 1; i > 0; --i)
            A[i] ^= A[i - 1];
        return A;
    }
};
