class Solution {
public:
    int minNumBooths(vector<string>& demand) {
        const int maxd = 26;
        vector<int> f(maxd), g(maxd);
        for(auto &it: demand) {
            for(char ch: it) {
                int o = ch - 'a';
                f[o] = max(f[o], ++g[o]);
            }
            for(char ch: it) {
                int o = ch - 'a';
                --g[o];
            }
        }
        return accumulate(f.begin(), f.end(), 0);
    }
};
