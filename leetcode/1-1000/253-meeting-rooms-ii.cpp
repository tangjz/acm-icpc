class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> que;
        for(auto &it: intervals) {
            que.push_back(it[0]);
            que.push_back(it[1]);
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int n = que.size();
        vector<int> ctr(n);
        for(auto &it: intervals) {
            int L = lower_bound(que.begin(), que.end(), it[0]) - que.begin();
            int R = lower_bound(que.begin(), que.end(), it[1]) - que.begin();
            ++ctr[L];
            --ctr[R];
        }
        int ans = 0;
        for(int i = 0; i + 1 < n; ++i) {
            ans = max(ans, ctr[i]);
            ctr[i + 1] += ctr[i];
        }
        return ans;
    }
};
