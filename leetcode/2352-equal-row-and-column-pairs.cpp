class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, pair<int, int> > mp;
        for(int i = 0; i < n; ++i) {
            ++mp[grid[i]].first;
            vector<int> vec(n);
            for(int j = 0; j < n; ++j)
                vec[j] = grid[j][i];
            ++mp[vec].second;
        }
        int ans = 0;
        for(auto &it: mp)
            ans += it.second.first * it.second.second;
        return ans;
    }
};
