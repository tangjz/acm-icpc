class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        const int maxd = 5;
        map<int, vector<int> > Hash;
        for(auto &it: items)
            Hash[it[0]].push_back(it[1]);
        vector<vector<int> > ret;
        ret.reserve(Hash.size());
        for(auto &it: Hash) {
            auto &vec = it.second;
            nth_element(vec.begin(), vec.begin() + maxd, vec.end(), greater<int>());
            int sum = 0;
            for(int i = 0; i < maxd; ++i)
                sum += vec[i];
            ret.push_back({it.first, sum / maxd});
        }
        return ret;
    }
};
