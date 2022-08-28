class Solution {
    static const int maxd = 10;
    void dfs(int dep, int val, int L, int R, vector<int> &ret) {
        if(val >= L)
            ret.push_back(val);
        if((++dep) < maxd && val <= (R - dep) / maxd)
            dfs(dep, val * maxd + dep, L, R, ret);
    }
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ret;
        for(int fir = 1; fir < maxd && fir <= high; ++fir)
            dfs(fir, fir, low, high, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }
};
