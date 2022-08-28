class Solution {
public:
    vector<int> diStringMatch(string s) {
        int las = 0, n = s.size();
        vector<int> ret(n + 1);
        for(int i = 0, j, k; i < n; i = j + 1) {
            for(j = i; j < n && s[j] == 'D'; ++j);
            for(k = j; k >= i; --k)
                ret[k] = las++;
        }
        if(s.back() == 'I')
            ret.back() = las++;
        return ret;
    }
};
