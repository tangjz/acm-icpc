class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int> > ret;
        unordered_map<int, vector<int> > Hash;
        int pos = 0;
        for(int x : groupSizes) {
            auto &it = Hash[x];
            it.push_back(pos++);
            if((int)it.size() == x) {
                ret.push_back(vector<int>());
                it.swap(ret.back());
            }
        }
        return ret;
    }
};
