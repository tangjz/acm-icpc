class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> psum = {0}, upp(n + n + 2);
        for(int x: hours) {
            int v = psum.back() + (x > 8 ? 1 : -1);
            upp[n + v] = max(upp[n + v], (int)psum.size());
            psum.push_back(v);
        }
        for(int i = n + n; i > 0; --i)
            upp[i - 1] = max(upp[i - 1], upp[i]);
        int ans = 0;
        for(int i = 0; i <= n; ++i)
            ans = max(ans, upp[n + psum[i] + 1] - i);
        return ans;
    }
};
