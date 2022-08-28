class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int mx = INT_MIN, sum = 0, p1 = 0, f1 = 0, p2 = 0, f2 = 0;
        for(int x : A) {
            mx = max(mx, x);
            sum += x;
            p1 = max(p1 + x, 0);
            f1 = max(f1, p1);
            p2 = max(p2 - x, 0);
            f2 = max(f2, p2);
        }
        return mx > 0 ? max(f1, sum + f2) : mx;
    }
};
