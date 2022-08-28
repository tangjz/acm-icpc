class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > ret;
        ret.push_back({});
        for(int x : nums) {
            vector<vector<int> > adt(ret.begin(), ret.end());
            for(auto &it : adt)
                it.push_back(x);
            ret.insert(ret.end(), adt.begin(), adt.end());
        }
        return ret;
    }
};
