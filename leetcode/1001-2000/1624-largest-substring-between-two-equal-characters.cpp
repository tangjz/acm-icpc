class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        const int maxd = 26;
        int n = s.size();
        vector<int> fir(maxd, INT_MAX), las(maxd, -1);
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            fir[o] = min(fir[o], i);
            las[o] = max(las[o], i);
        }
        int ans = -1;
        for(int i = 0; i < maxd; ++i)
            if(fir[i] < las[i])
                ans = max(ans, las[i] - fir[i] - 1);
        return ans;
    }
};
