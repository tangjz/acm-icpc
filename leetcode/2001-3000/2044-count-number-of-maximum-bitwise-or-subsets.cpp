class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        unordered_map<int, int> f;
        f[0] = 1;
        for(int x: nums) {
            unordered_map<int, int> g;
            for(auto &it: f) {
                g[it.first] += it.second;
                g[it.first | x] += it.second;
            }
            f = move(g);
        }
        int upp = 0;
        for(auto &it: f)
            upp = max(upp, it.first);
        return f[upp];
    }
};
