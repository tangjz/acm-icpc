class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int x = m, y = n;
        for(auto &it: ops) {
            x = min(x, it[0]);
            y = min(y, it[1]);
        }
        return x * y;
    }
};
