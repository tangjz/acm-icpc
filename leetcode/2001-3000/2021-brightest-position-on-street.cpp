class Solution {
public:
    int brightestPosition(vector<vector<int>>& lights) {
        vector<int> que;
        for(auto &it: lights) {
            int p = it[0], dt = it[1];
            que.push_back(p - dt);
            que.push_back(p + dt + 1);
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        vector<int> ctr(que.size());
        for(auto &it: lights) {
            int p = it[0], dt = it[1];
            ++ctr[lower_bound(que.begin(), que.end(), p - dt) - que.begin()];
            --ctr[lower_bound(que.begin(), que.end(), p + dt + 1) - que.begin()];
        }
        int ans = que[0], best = ctr[0];
        for(int i = 1; i < (int)que.size(); ++i) {
            ctr[i] += ctr[i - 1];
            if(best < ctr[i]) {
                best = ctr[i];
                ans = que[i];
            }
        }
        return ans;
    }
};
