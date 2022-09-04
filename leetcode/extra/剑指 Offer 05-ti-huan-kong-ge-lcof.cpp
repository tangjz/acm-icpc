class Solution {
public:
    string replaceSpace(string s) {
        int n = s.size(), cnt = 0;
        for(int i = 0; i < n; ++i)
            cnt += s[i] == ' ';
        int m = n + cnt + cnt;
        s.resize(m);
        for(int i = n - 1; i >= 0; --i)
            if(s[i] == ' ') {
                s[--m] = '0';
                s[--m] = '2';
                s[--m] = '%';
            } else {
                s[--m] = s[i];
            }
        return s;
    }
};
