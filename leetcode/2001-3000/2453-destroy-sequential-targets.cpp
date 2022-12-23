class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) {
        unordered_map<int, pair<int, int> > ctr;
        pair<int, int> ans = {0, INT_MIN};
        for(int x: nums) {
            int y = x % space;
            auto &it = ctr.insert({y, {0, INT_MIN}}).first -> second;
            ++it.first;
            it.second = max(it.second, -x);
            ans = max(ans, it);
        }
        return -ans.second;
    }
};
