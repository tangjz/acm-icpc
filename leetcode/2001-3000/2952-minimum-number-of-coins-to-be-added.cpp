class Solution {
public:
    int minimumAddedCoins(vector<int>& A, int lim) {
        int ans = 0;
        long long cur = 0;
        sort(A.begin(), A.end());
        for(int x: A) {
            while(x > cur + 1) {
                ++ans;
                cur += cur + 1;
            }
            cur += x;
        }
        while(cur < lim) {
            ++ans;
            cur += cur + 1;
        }
        return ans;
    }
};
