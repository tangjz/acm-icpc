class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> que(n << 1);
        for(int i = 0; i < n; ++i) {
            que[i << 1] = positions[i][0];
            que[i << 1 | 1] = positions[i][0] + positions[i][1];
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> upp(m), ans;
        ans.reserve(n);
        for(auto &it: positions) {
            int L = lower_bound(que.begin(), que.end(), it[0]) - que.begin();
            int R = lower_bound(que.begin(), que.end(), it[0] + it[1]) - que.begin();
            int mx = *max_element(upp.begin() + L, upp.begin() + R) + it[1];
            for(int i = L; i < R; ++i)
                upp[i] = mx;
            ans.push_back(ans.empty() ? mx : max(ans.back(), mx));
        }
        return ans;
    }
};
