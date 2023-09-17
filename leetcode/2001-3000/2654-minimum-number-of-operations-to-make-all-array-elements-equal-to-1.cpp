class Solution {
public:
    int minOperations(vector<int>& A) {
        int n = A.size(), ans = INT_MAX, cnt = 0;
        for(int i = 0; i < n; ++i) {
            cnt += A[i] == 1;
            for(int j = i, com = 0; j < n && j - i < ans; ++j) {
                com = gcd(com, A[j]);
                if(com == 1) {
                    ans = j - i;
                    break;
                }
            }
        }
        return ans < INT_MAX ? ans + n - !cnt - cnt : -1;
    }
};
