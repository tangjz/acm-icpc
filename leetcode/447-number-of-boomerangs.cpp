class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        unordered_map<int, int> ctr;
        for(int i = 0; i < n; ++i) {
            ctr.clear();
            for(int j = 0; j < n; ++j) {
                if(i == j)
                    continue;
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                ans += ctr[dx * dx + dy * dy]++;
            }
        }
        return ans * 2;
    }
};
