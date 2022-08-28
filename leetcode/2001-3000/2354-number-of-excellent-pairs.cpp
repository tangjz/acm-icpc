class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        typedef long long LL;
        const int maxd = 31;
        vector<set<int> > sp(maxd);
        for(int x: nums) {
            int c = __builtin_popcount(x);
            sp[c].insert(x);
        }
        LL ans = 0;
        for(int i = 0, j = maxd - 1, c = 0; i < maxd; ++i) {
            for( ; j >= 0 && i + j >= k; c += sp[j--].size());
            ans += (LL)sp[i].size() * c;
        }
        return ans;
    }
};
