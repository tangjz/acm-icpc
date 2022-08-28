class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        vector<vector<int> > f = {{}};
        for(auto &it: ctr) {
            vector<vector<int> > g;
            for(auto &vec: f) {
                vector<int> nxt(vec.begin(), vec.end());
                for(int i = 0; i < it.second; ++i) {
                    nxt.push_back(it.first);
                    g.push_back(nxt);
                }
            }
            f.insert(f.end(), g.begin(), g.end());
        }
        return f;
    }
};
