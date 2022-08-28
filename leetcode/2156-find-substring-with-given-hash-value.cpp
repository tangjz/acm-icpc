class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        typedef long long LL;
        int n = s.size();
        vector<int> hs(n + 1);
        for(int i = n - 1; i >= 0; --i) {
            hs[i] = (s[i] - 'a' + 1 + (LL)power * hs[i + 1]) % modulo;
        }
        int mul = 1;
        for(int i = 0; i < k; ++i)
            mul = (LL)power * mul % modulo;
        for(int i = 0; i <= n - k; ++i)
            if(hs[i] == (hashValue + (LL)mul * hs[i + k]) % modulo)
                return s.substr(i, k);
        return "";
    }
};
