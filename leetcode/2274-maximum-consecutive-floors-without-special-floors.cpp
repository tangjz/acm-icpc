class Solution {
public:
    int maxConsecutive(int L, int R, vector<int>& A) {
        int n = A.size(), ans = 0, las = L - 1;
        sort(A.begin(), A.end());
        for(int x: A) {
            ans = max(ans, x - las - 1);
            las = x;
        }
        ans = max(ans, R - las);
        return ans;
    }
};
