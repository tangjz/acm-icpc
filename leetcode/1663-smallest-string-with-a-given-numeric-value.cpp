class Solution {
public:
    string getSmallestString(int n, int k) {
        string ans = "";
        k -= n;
        for(int i = 0; i < n; ++i) {
            int x = max(k - 25 * (n - 1 - i), 0);
            ans += 'a' + x;
            k -= x;
        }
        return ans;
    }
};
