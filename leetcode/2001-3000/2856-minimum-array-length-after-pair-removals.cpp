class Solution {
public:
    int minLengthAfterRemovals(vector<int>& A) {
        int n = A.size(), upp = 0;
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && A[i] == A[j]; ++j);
            upp = max(upp, j - i);
        }
        return max(n & 1, upp + upp - n);
    }
};
