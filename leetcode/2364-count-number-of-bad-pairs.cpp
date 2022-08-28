class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        typedef long long LL;
        int tot = 0;
        LL ans = 0;
        unordered_map<int, int> ctr;
        for(int x: nums) {
            ans += tot - (ctr[tot - x]++);
            ++tot;
        }
        return ans;
    }
};
