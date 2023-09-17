class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<int> pos;
        for(auto &it: intervals) {
            pos.push_back(it[0] << 1);
            pos.push_back(it[1] << 1 | 1);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        vector<int> psum(pos.size());
        for(auto &it: intervals) {
            int L = lower_bound(pos.begin(), pos.end(), it[0] << 1) - pos.begin();
            int R = lower_bound(pos.begin(), pos.end(), it[1] << 1 | 1) - pos.begin();
            psum[L] += 1;
            psum[R] -= 1;
        }
        vector<vector<int> > ret;
        for(int i = 0; i + 1 < (int)pos.size(); ++i) {
            psum[i + 1] += psum[i];
            if(!psum[i])
                continue;
            if(i > 0 && psum[i - 1] > 0) {
                ret.back()[1] = pos[i + 1] >> 1;
            } else {
                ret.push_back({pos[i] >> 1, pos[i + 1] >> 1});
            }
        }
        return ret;
    }
};
