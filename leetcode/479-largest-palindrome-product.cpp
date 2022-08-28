class Solution {
public:
    int largestPalindrome(int n) {
        typedef long long LL;
        const int mod = 1337;
        int pw = 1;
        for(int i = 0; i < n; ++i)
            pw *= 10;
        int L = pw / 10, R = pw;
        for(int i = R - 1; i >= L; --i) {
            string s = to_string(i), rev_s = s;
            reverse(rev_s.begin(), rev_s.end());
            LL x = stol(s + rev_s);
            for(int j = min(R - 1LL, x / L); (LL)j * j >= x; --j)
                if(x % j == 0)
                    return x % mod;
        }
        for(int i = R - 1; i >= L; --i) {
            string s = to_string(i), rev_s = s;
            reverse(rev_s.begin(), rev_s.end());
            s.pop_back();
            LL x = stol(s + rev_s);
            for(int j = min(R - 1LL, x / L); (LL)j * j >= x; --j)
                if(x % j == 0)
                    return x % mod;
        }
        return -1;
    }
};
