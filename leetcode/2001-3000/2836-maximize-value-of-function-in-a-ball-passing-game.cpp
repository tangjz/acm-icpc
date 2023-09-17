class Solution {
public:
    long long getMaxFunctionValue(vector<int>& p, long long k) {
        typedef long long LL;
        int n = p.size();
        vector<int> c(n), pc(n), nc(n);
        vector<LL> s(n), ps(n), ns(n);
        for(int i = 0; i < n; ++i) {
            nc[i] = p[i];
            ns[i] = p[i];
            c[i] = s[i] = i;
        }
        for( ; k > 0; k >>= 1) {
            if(k & 1) {
                for(int i = 0; i < n; ++i) {
                    s[i] += ns[c[i]];
                    c[i] = nc[c[i]];
                }
            }
            pc.swap(nc);
            ps.swap(ns);
            for(int i = 0; i < n; ++i) {
                nc[i] = pc[pc[i]];
                ns[i] = ps[i] + ps[pc[i]];
            }
        }
        return *max_element(s.begin(), s.end());
    }
};
