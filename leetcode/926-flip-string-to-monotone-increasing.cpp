class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        vector<int> psum = {0};
        for(char ch: s)
            psum.push_back(psum.back() + (ch == '1'));
        int ans = n;
        for(int i = 0; i <= n; ++i) {
            int tmp = psum[i] + n - i - (psum[n] - psum[i]);
            ans = min(ans, tmp);
        }
        return ans;
    }
};
