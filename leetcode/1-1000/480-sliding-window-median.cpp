class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        set<pair<int, int> > lft, rht;
        vector<double> ret;
        ret.reserve(n - k + 1);
        for(int i = 0; i < n; ++i) {
            if(rht.empty() || nums[i] >= rht.begin() -> first) {
                rht.insert({nums[i], i});
            } else {
                lft.insert({nums[i], i});
            }
            if(lft.size() > rht.size()) {
                pair<int, int> tmp = *lft.rbegin();
                rht.insert(tmp);
                lft.erase(tmp);
            } else if(lft.size() + 1 < rht.size()) {
                pair<int, int> tmp = *rht.begin();
                lft.insert(tmp);
                rht.erase(tmp);
            }
            if(i < k - 1)
                continue;
            if(k & 1) {
                ret.push_back((double)(rht.begin() -> first));
            } else {
                ret.push_back(((double)(lft.rbegin() -> first) + rht.begin() -> first) / 2);
            }
            pair<int, int> tmp = {nums[i - k + 1], i - k + 1};
            if(rht.count(tmp)) {
                rht.erase(tmp);
            } else {
                lft.erase(tmp);
            }
            if(lft.size() > rht.size()) {
                pair<int, int> tmp = *lft.rbegin();
                rht.insert(tmp);
                lft.erase(tmp);
            } else if(lft.size() + 1 < rht.size()) {
                pair<int, int> tmp = *rht.begin();
                lft.insert(tmp);
                rht.erase(tmp);
            }
        }
        return ret;
    }
};
