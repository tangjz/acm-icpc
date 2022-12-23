class Solution {
public:
    int countAnagrams(string s) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = s.size();
        vector<int> inv(n + 1);
        inv[1] = 1;
        for(int i = 2; i <= n; ++i)
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        int ans = 1;
        unordered_map<char, int> ctr;
        for(int i = 0, j; i < n; ) {
            if(s[i] == ' ') {
                ++i;
                continue;
            }
            ctr.clear();
            for(j = i; i < n && s[i] != ' '; ++i) {
                ans = (LL)ans * (i - j + 1LL) % mod * inv[++ctr[s[i]]] % mod;
            }
        }
        return ans;
    }
};
