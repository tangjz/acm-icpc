class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = (int)nums.size();
        sort(nums.begin(), nums.end());
        vector<pair<int, int> > seq;
        for(int x: nums)
            if(seq.empty() || seq.back().first != x) {
                seq.push_back({x, 1});
            } else {
                ++seq.back().second;
            }
        n = (int)seq.size();
        vector<vector<int> > ret;
        for(int j = 0; j < n; ++j) {
            for(int i = j, k = j; i >= 0 && k < n; ) {
                int val = seq[i].first + seq[j].first + seq[k].first;
                if(val < 0) {
                    ++k;
                } else if(val > 0) {
                    --i;
                } else {
                    if(1 + (i == j) + (j == k) <= seq[j].second)
                        ret.push_back({seq[i].first, seq[j].first, seq[k].first});
                    ++k;
                    --i;
                }
            }
        }
        return ret;
    }
};
