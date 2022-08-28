class Solution {
public:
    int findCenter(vector<vector<int>>& e) {
        int x = e[0][0], y = e[0][1];
        int dx = 0, dy = 0;
        for(auto &it : e)
            for(int z: it) {
                dx += z == x;
                dy += z == y;
            }
        return dx < dy ? y : x;
    }
};
