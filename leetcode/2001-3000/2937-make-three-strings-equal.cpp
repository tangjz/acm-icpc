class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        vector<string> s = {s1, s2, s3};
        int sz[3] = {}, n = INT_MAX;
        for(int i = 0; i < 3; ++i) {
            sz[i] = s[i].size();
            n = min(n, sz[i]);
        }
        for(int i = 0; i < n; ++i) {
            bool bad = 0;
            for(int j = 1; !bad && j < 3; ++j)
                bad |= s[0][i] != s[j][i];
            if(bad)
                n = i;
        }
        return n ? sz[0] + sz[1] + sz[2] - n * 3 : -1;
    }
};
