class Solution {
public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        typedef long long LL;
        LL las = 0, upp = 0;
        vector<LL> ret;
        for(int x: nums) {
            upp = max(upp, (LL)x);
            las += upp + x;
            ret.push_back(las);
        }
        return ret;
    }
};
