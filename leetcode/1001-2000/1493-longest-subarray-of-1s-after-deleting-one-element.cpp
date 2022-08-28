class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        vector<pair<int, int> > seq;
        for(int x : nums)
            if(seq.empty() || seq.back().first != x) {
                seq.push_back({x, 1});
            } else {
                ++seq.back().second;
            }
        int ret = 0, tot = (int)seq.size();
        for(int i = 0; i < tot; ++i)
            if(seq[i].first) {
                ret = max(ret, seq[i].second);
            } else if(seq[i].second == 1 && i > 0 && i + 1 < tot) {
                ret = max(ret, seq[i - 1].second + seq[i + 1].second);
            }
        return ret < (int)nums.size() ? ret : ret - 1;
    }
};
