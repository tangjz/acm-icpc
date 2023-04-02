class Solution {
public:
    int miceAndCheese(vector<int>& A, vector<int>& B, int k) {
        int n = A.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            A[i] -= B[i];
            ans += B[i];
        }
        sort(A.begin(), A.end());
        while(k--) {
            ans += A.back();
            A.pop_back();
        }
        return ans;
    }
};
