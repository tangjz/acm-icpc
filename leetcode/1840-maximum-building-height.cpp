class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& upp) {
        upp.push_back({1, 0});
        upp.push_back({n, n});
        sort(upp.begin(), upp.end());
        int m = (int)upp.size();
        for(int i = 1; i < m; ++i) {
            int dt = upp[i][0] - upp[i - 1][0];
            upp[i][1] = min(upp[i][1], upp[i - 1][1] + dt);
        }
        for(int i = m - 1; i > 0; --i) {
            int dt = upp[i][0] - upp[i - 1][0];
            upp[i - 1][1] = min(upp[i - 1][1], upp[i][1] + dt);
        }
        int ans = 0;
        for(int i = 0; i < m; ++i) {
            ans = max(ans, upp[i][1]);
            if(i > 0) {
                int dt = upp[i][0] - upp[i - 1][0];
                int u = upp[i][1], v = upp[i - 1][1];
                if(u > v)
                    swap(u, v);
                ans = max(ans, v + (dt - (v - u)) / 2);
                // printf("mid %d %d: %d\n", upp[i - 1][0], upp[i][0], v + (dt - (v - u)) / 2);
            }
            // printf("upp %d: %d\n", upp[i][0], upp[i][1]);
        }
        return ans;
    }
};
