class Solution {
public:
    long long countTheNumOfKFreeSubsets(vector<int>& nums, int k) {
        typedef long long LL;
        unordered_map<int, pair<LL, LL> > sp;
        sort(nums.begin(), nums.end());
        for(int x: nums) {
            pair<LL, LL> ways = {1, 0};
            auto it = sp.find(x - k);
            if(it != sp.end()) {
                ways = it -> second;
                sp.erase(it);
            }
            sp.insert({x, {ways.first + ways.second, ways.first}});
        }
        LL ans = 1;
        for(auto &it: sp)
            ans *= it.second.first + it.second.second;
        return ans;
    }
};
