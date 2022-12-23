class Solution {
public:
    int subarrayLCM(vector<int>& A, int k) {
        int n = A.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            int lcm = 1;
            for(int j = i; lcm <= k && j < n; ++j) {
                lcm *= A[j] / gcd(lcm, A[j]);
                ans += lcm == k;
            }
        }
        return ans;
    }
};
