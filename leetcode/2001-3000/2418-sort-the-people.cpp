class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        int n = names.size();
        map<int, int> mp;
        for(int i = 0; i < n; ++i)
            mp[-heights[i]] = i;
        vector<string> ret;
        for(auto &it: mp)
            ret.push_back(move(names[it.second]));
        return ret;
    }
};
