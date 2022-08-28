class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int ret = 0;
        for(auto &it : grid)
            for(int x : it)
                ret += x < 0;
        return ret;
    }
};
