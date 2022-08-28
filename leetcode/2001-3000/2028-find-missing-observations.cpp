class Solution {
public:
    vector<int> missingRolls(vector<int>& A, int mean, int n) {
        int m = A.size();
        int sum = mean * (n + m);
        for(int x: A)
            sum -= x;
        if(sum < n || sum > n * 6)
            return {};
        sum -= n;
        vector<int> B(n, 1);
        for(int i = 0; i < n; ++i) {
            int tmp = min(sum, 5);
            sum -= tmp;
            B[i] += tmp;
        }
        return B;
    }
};
