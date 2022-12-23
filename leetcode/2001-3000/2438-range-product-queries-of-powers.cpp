class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> seq, ret;
        for(int i = 1; i <= n; i <<= 1)
            if(n & i)
                seq.push_back(i);
        const int mod = (int)1e9 + 7;
        for(auto &it: queries) {
            int prd = 1;
            for(int i = it[0]; i <= it[1]; ++i)
                prd = 1LL * prd * seq[i] % mod;
            ret.push_back(prd);
        }
        return ret;
    }
};
