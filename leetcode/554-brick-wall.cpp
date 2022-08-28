class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        vector<int> que;
        for(auto &row: wall) {
            int L, R = 0;
            for(int x: row) {
                L = R;
                R = L + x;
                if(L < R) {
                    que.push_back(L + 1);
                    que.push_back(R);
                }
            }
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        vector<int> ctr(que.size());
        for(auto &row: wall) {
            int L, R = 0;
            for(int x: row) {
                L = R;
                R = L + x;
                if(L < R) {
                    ++ctr[lower_bound(que.begin(), que.end(), L + 1) - que.begin()];
                    --ctr[lower_bound(que.begin(), que.end(), R) - que.begin()];
                }
            }
        }
        int ans = wall.size(), pre = 0;
        ctr.pop_back();
        for(int x: ctr) {
            pre += x;
            ans = min(ans, pre);
        }
        return ans;
    }
};
