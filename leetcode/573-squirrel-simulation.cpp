class Solution {
public:
    int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {
        int n = nuts.size(), ans = 0, low = INT_MAX;
        for(auto &nut: nuts) {
            int dis0 = abs(tree[0] - nut[0]) + abs(tree[1] - nut[1]);
            int dis1 = abs(squirrel[0] - nut[0]) + abs(squirrel[1] - nut[1]);
            ans += dis0 + dis0;
            low = min(low, dis1 - dis0);
        }
        return ans + low;
    }
};
