class Solution {
public:
    long long findTheArrayConcVal(vector<int>& A) {
        typedef long long LL;
        int n = A.size();
        LL ans = 0;
        for(int i = 0, j = n - 1; i <= j; ++i, --j) {
            if(i == j) {
                ans += A[i];
                continue;
            }
            string s = to_string(A[i]) + to_string(A[j]);
            ans += stol(s);
        }
        return ans;
    }
};
