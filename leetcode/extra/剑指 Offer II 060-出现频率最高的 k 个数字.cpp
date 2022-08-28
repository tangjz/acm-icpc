class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> ctr;
        for(int x : nums)
            ++ctr[x];
        vector<pair<int, int> > seq;
        for(auto &it : ctr)
            seq.push_back({-it.second, it.first});
        nth_element(seq.begin(), seq.begin() + k, seq.end());
        seq.resize(k);
        vector<int> ret;
        for(auto &it : seq)
            ret.push_back(it.second);
        return ret;
    }
};
