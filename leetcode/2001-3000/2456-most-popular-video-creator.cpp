class Solution {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        int n = ids.size();
        long long upp = 0;
        map<string, pair<long long, pair<int, string> > > mp;
        for(int i = 0; i < n; ++i) {
            auto &it = mp.insert({creators[i], {0, {-views[i], ids[i]}}}).first -> second;
            upp = max(upp, it.first += views[i]);
            it.second = min(it.second, make_pair(-views[i], ids[i]));
        }
        vector<vector<string> > ret;
        for(auto &it: mp)
            if(it.second.first == upp)
                ret.push_back({it.first, it.second.second.second});
        return ret;
    }
};
