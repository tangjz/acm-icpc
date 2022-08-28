class Solution {
public:
    int minOperations(vector<int>& A) {
        int n = A.size();
        vector<int> B(n), C(n);
        for(int i = 0; i < n; ++i) {
            for( ; A[i] % 2 == 0; A[i] /= 2, ++B[i]);
            for( ; A[i] % 3 == 0; A[i] /= 3, ++C[i]);
            if(A[i] != A[0])
                return -1;
        }
        int ans = 0;
        int uppB = *max_element(B.begin(), B.end());
        int uppC = *max_element(C.begin(), C.end());
        for(int i = 0; i < n; ++i) {
            ans += uppB - B[i];
            ans += uppC - C[i];
        }
        return ans;
    }
};
