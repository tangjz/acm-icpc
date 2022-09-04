class Solution {
public:
    long long minimumMoney(vector<vector<int>>& seq) {
        sort(seq.begin(), seq.end(), [&](auto const &u, auto const &v) {
            int su = u[0] < u[1], sv = v[0] < v[1];
            if(su != sv)
                return su < sv;
            if(!su)
                return u[1] < v[1];
            return u[0] > v[0];
        });
        long long ans = 0, cur = 0;
        for(auto &it: seq) {
            cur += it[0];
            ans = max(ans, cur);
            cur -= it[1];
        }
        return ans;
    }
};
