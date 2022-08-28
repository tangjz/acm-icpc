class Solution {
public:
    int edgeScore(vector<int>& edges) {
        typedef long long LL;
        int n = edges.size();
        vector<LL> f(n);
        for(int i = 0; i < n; ++i)
            f[edges[i]] += i;
        int pos = -1;
        LL best = -1;
        for(int i = 0; i < n; ++i)
            if(best < f[i]) {
                best = f[i];
                pos = i;
            }
        return pos;
    }
};
