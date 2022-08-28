class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        int n = 0;
        for(char ch: s)
            if(ch != '-')
                s[n++] = toupper(ch);
        int m = n + (n - 1) / k, p = m;
        if(s.size() < m)
            s.resize(m);
        while(n > k) {
            for(int i = 0; i < k; ++i)
                s[--p] = s[--n];
            s[--p] = '-';
        }
        s.resize(m);
        return s;
    }
};
