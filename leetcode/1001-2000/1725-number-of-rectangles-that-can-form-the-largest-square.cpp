class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rect) {
        int cnt = 0, mx = 0;
        for(auto &it : rect) {
            int tp = min(it[0], it[1]);
            if(mx < tp) {
                mx = tp;
                cnt = 0;
            }
            cnt += mx == tp;
        }
        return cnt;
    }
};
