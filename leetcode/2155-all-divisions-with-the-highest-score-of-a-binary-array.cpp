class Solution {
public:
    vector<int> maxScoreIndices(vector<int>& nums) {
        int ans = 0, cur = 0, pos = 0;
        vector<int> ret = {0};
        for(int x: nums) {
            cur += x ? -1 : 1;
            if(ans < cur) {
                ans = cur;
                ret = {};
            }
            ++pos;
            if(ans == cur) {
                ret.push_back(pos);
            }
        }
        return ret;
    }
};
