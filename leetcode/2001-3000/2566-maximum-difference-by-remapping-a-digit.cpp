class Solution {
public:
    int minMaxDifference(int num) {
        string s = to_string(num), t = to_string(num);
        int n = s.size(), p = 0, q = 0;
        for( ; p < n && s[p] == '9'; ++p);
        for( ; q < n && s[q] == '0'; ++q);
        for(int i = n - 1; i >= 0; --i) {
            if(i >= p && s[i] == s[p])
                s[i] = '9';
            if(i >= q && t[i] == t[q])
                t[i] = '0';
        }
        return stoi(s) - stoi(t);
    }
};
