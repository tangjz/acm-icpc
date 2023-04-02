class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        unordered_map<int, int> ctr;
        vector<vector<int> > ret;
        for(int x: nums)
            ++ctr[x];
        for(auto &it: ctr) {
            if(ret.size() < it.second)
                ret.resize(it.second);
            for(int i = 0; i < it.second; ++i)
                ret[i].push_back(it.first);
        }
        return ret;
    }
};
