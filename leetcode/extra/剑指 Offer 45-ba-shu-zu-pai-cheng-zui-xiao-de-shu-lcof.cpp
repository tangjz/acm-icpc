class Solution {
public:
    string minNumber(vector<int>& nums) {
        vector<string> cand;
        for(int x: nums)
            cand.push_back(to_string(x));
        sort(cand.begin(), cand.end(), [&](auto const &u, auto const &v) {
            return u + v < v + u;
        });
        string ret;
        for(auto &it: cand)
            ret += it;
        return ret;
    }
};
