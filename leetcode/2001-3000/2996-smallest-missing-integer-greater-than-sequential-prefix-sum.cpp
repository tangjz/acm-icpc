class Solution {
public:
    int missingInteger(vector<int>& A) {
        int n = A.size(), s = A[0];
        for(int i = 1; i < n && A[i] - 1 == A[i - 1]; ++i)
            s += A[i];
        unordered_set<int> sp(A.begin(), A.end());
        for( ; sp.count(s); ++s);
        return s;
    }
};
