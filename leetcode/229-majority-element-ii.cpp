class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        pair<int, int> info[2] = {};
        for(int x : nums) {
            int idx;
            for(idx = 0; idx < 2; ++idx)
                if(info[idx].first == x) {
                    ++info[idx].second;
                    break;
                }
            if(idx == 2)
                for(idx = 0; idx < 2; ++idx)
                    if(!info[idx].second) {
                        info[idx] = {x, 1};
                        break;
                    }
            if(idx == 2)
                for(idx = 0; idx < 2; ++idx)
                    --info[idx].second;
        }
        for(int idx = 0; idx < 2; ++idx)
            if(!info[idx].second) {
                info[idx].second = INT_MIN;
            } else {
                info[idx].second = 0;
            }
        for(int x : nums)
            for(int idx = 0; idx < 2; ++idx)
                if(info[idx].first == x) {
                    ++info[idx].second;
                    break;
                }
        int threshold = (int)nums.size() / 3;
        vector<int> ret;
        for(int idx = 0; idx < 2; ++idx)
            if(info[idx].second > threshold)
                ret.push_back(info[idx].first);
        return ret;
    }
};
