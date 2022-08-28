class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> ctr;
        for(auto &it: words)
            ++ctr[it];
        vector<pair<int, string> > seq;
        seq.reserve(ctr.size());
        for(auto &it: ctr)
            seq.push_back({-it.second, it.first});
        sort(seq.begin(), seq.end());
        seq.resize(k);
        vector<string> ret;
        ret.reserve(k);
        for(auto &it: seq)
            ret.push_back(it.second);
        return ret;
    }
};
