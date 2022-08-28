class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        const int maxd = 6;
        int n = tops.size();
        vector<int> pos[2][maxd], vec[2];
        vec[0] = move(tops);
        vec[1] = move(bottoms);
        for(int i = 0; i < n; ++i) {
            pos[0][--vec[0][i]].push_back(i);
            pos[1][--vec[1][i]].push_back(i);
        }
        int ans = n + 1;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < maxd; ++j) {
                int c0 = pos[i][j].size(), c1 = pos[!i][j].size();
                for(int k: pos[i][j])
                    c1 -= vec[!i][k] == j;
                if(c0 + c1 == n)
                    ans = min(ans, c1);
            }
        }
        return ans <= n ? ans : -1;
    }
};
