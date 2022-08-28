class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int n = str1.size(), m = str2.size(), r = gcd(n, m);
        for(int ans = r; ans >= 1; --ans) {
            if(r % ans > 0)
                continue;
            bool chk = 1;
            for(int i = 0; chk && i < n; ++i)
                chk &= str1[i] == str1[i % ans];
            for(int i = 0; chk && i < m; ++i)
                chk &= str2[i] == str1[i % ans];
            if(chk)
                return str1.substr(0, ans);
        }
        return "";
    }
};
