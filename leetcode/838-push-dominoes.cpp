class Solution {
public:
    string pushDominoes(string s) {
        int n = s.size(), las = -1;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '.')
                continue;
            if(s[i] == 'L') {
                if(las == -1 || s[las] == 'L') {
                    for(int j = las + 1; j < i; ++j)
                        s[j] = 'L';
                } else {
                    for(int j = las + 1, k = i - 1; j < k; ++j, --k) {
                        s[j] = 'R';
                        s[k] = 'L';
                    }
                }
            } else if(s[i] == 'R') {
                if(las != -1 && s[las] == 'R') {
                    for(int j = las + 1; j < i; ++j)
                        s[j] = 'R';
                }
            }
            las = i;
        }
        if(las != -1 && s[las] == 'R')
            for(int j = las + 1; j < n; ++j)
                s[j] = 'R';
        return s;
    }
};
