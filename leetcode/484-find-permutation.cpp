class Solution {
public:
    vector<int> findPermutation(string s) {
        int n = s.size(), las = 0;
        vector<int> perm(n + 1);
        for(int i = 0, j = 0; i < n; i = j + 1) {
            for(j = i; j < n && s[j] == 'D'; ++j);
            for(int k = j; k >= i; --k)
                perm[k] = ++las;
        }
        if(s.back() == 'I')
            perm.back() = ++las;
        return perm;
    }
};
