class Solution {
public:
    long long numberOfWays(string s) {
        int n = s.size();
        vector<int> psum = {0};
        for(char ch: s)
            psum.push_back(psum.back() + (ch == '1'));
        long long ans = 0;
        for(int i = 1; i <= n; ++i) {
            int L = psum[i - 1], M = s[i - 1] == '1', R = psum[n] - psum[i];
            if(M) {
                L = i - 1 - L;
                R = n - i - R;
            }
            ans += 1LL * L * R;
        }
        return ans;
    }
};
