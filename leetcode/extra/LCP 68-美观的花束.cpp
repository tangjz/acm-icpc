class Solution {
public:
    int beautifulBouquet(vector<int>& flowers, int cnt) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = flowers.size();
        unordered_map<int, int> ctr;
        LL ans = 0;
        for(int i = 0, j = 0, c = 0; i < n; ++i) {
            for( ; j < n && !c; ++j) {
                int v = flowers[j];
                c += (++ctr[v]) == cnt + 1;
            }
            ans += j - i - !!c;
            int v = flowers[i];
            c -= (--ctr[v]) == cnt;
        }
        return ans % mod;
    }
};
