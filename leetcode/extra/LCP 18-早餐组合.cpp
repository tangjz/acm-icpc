class Solution {
public:
    int breakfastNumber(vector<int>& A, vector<int>& B, int x) {
        int n = A.size(), m = B.size();
        long long ans = 0;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        for(int i = 0, j = m - 1; i < n; ++i) {
            for( ; j >= 0 && A[i] + B[j] > x; --j);
            if(j == -1)
                break;
            ans += j + 1;
        }
        return ans % ((int)1e9 + 7);
    }
};
