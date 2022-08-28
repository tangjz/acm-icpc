class Solution {
public:
    int numFlowers(vector<vector<int>>& roads) {
        int n = roads.size() + 1;
        vector<int> deg(n, 1);
        for(auto &it: roads) {
            ++deg[it[0]];
            ++deg[it[1]];
        }
        return *max_element(deg.begin(), deg.end());
    }
};
