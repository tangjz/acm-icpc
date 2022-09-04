class Solution {
public:
    int minGroups(vector<vector<int>>& seg) {
        int n = seg.size();
        vector<int> que;
        que.reserve(n + n);
        for(auto &it: seg) {
            que.push_back(it[0]);
            que.push_back(++it[1]);
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> ctr(m);
        for(auto &it: seg) {
            ++ctr[lower_bound(que.begin(), que.end(), it[0]) - que.begin()];
            --ctr[lower_bound(que.begin(), que.end(), it[1]) - que.begin()];
        }
        int ans = 0;
        for(int i = 0; i < m; ++i) {
            if(i > 0)
                ctr[i] += ctr[i - 1];
            ans = max(ans, ctr[i]);
        }
        return ans;
    }
};
