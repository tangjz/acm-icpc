class Solution {
public:
    vector<int> findOriginalArray(vector<int>& A) {
        int n = A.size();
        if(n & 1)
            return {};
        vector<int> B;
        sort(A.begin(), A.end());
        for(int i = 0, j = 0; i < n; ++i) {
            if(A[i] == -1)
                continue;
            B.push_back(A[i]);
            A[i] = -1;
            for( ; j < n && A[j] < B.back() * 2; ++j);
            if(j < n && A[j] == B.back() * 2) {
                A[j] = -1;
            } else {
                return {};
            }
        }
        return B;
    }
};
