class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        int upp = 1;
        for(auto &it: queries)
            upp = max(upp, it[1]);
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        vector<int> d(upp + 1), pr, inv(upp + 1);
        d[1] = inv[1] = 1;
        for(int i = 2; i <= upp; ++i) {
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p: pr) {
                int j = i * p;
                if(j > upp)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
        vector<int> ans;
        for(auto &it: queries) {
            int ways = 1;
            for(int tmp = it[1]; tmp > 1; ) {
                int p = d[tmp], e = 0;
                for( ; d[tmp] == p; tmp /= p, ++e, ways = (LL)ways * (it[0] + e - 1) % mod * inv[e] % mod);
            }
            ans.push_back(ways);
        }
        return ans;
    }
};
