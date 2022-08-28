class Solution {
public:
    bool canReceiveAllSignals(vector<vector<int>>& intervals) {
        vector<int> pos;
        for(auto &it: intervals) {
            pos.push_back(it[0]);
            pos.push_back(it[1]);
        }
        sort(pos.begin(), pos.end());
        vector<int> ctr(pos.size());
        for(auto &it: intervals) {
            ++ctr[lower_bound(pos.begin(), pos.end(), it[0]) - pos.begin()];
            --ctr[lower_bound(pos.begin(), pos.end(), it[1]) - pos.begin()];
        }
        int sum = 0;
        for(int x: ctr) {
            if((sum += x) > 1)
                return 0;
        }
        return 1;
    }
};
