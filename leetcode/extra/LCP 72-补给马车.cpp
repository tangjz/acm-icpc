class Solution {
public:
    vector<int> supplyWagon(vector<int>& A) {
        int n = A.size() / 2;
        for(int m; (m = A.size()) > n; ) {
            int p = 0, s = INT_MAX;
            for(int i = 1; i < m; ++i) {
                int c = A[i - 1] + A[i];
                if(c < s) {
                    s = c;
                    p = i;
                }
            }
            A[p - 1] += A[p];
            if(p + 1 < m)
                rotate(A.begin() + p, A.begin() + p + 1, A.end());
            A.pop_back();
        }
        return A;
    }
};
