class Solution {
public:
    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& seg) {
        vector<int> que;
        for(auto &it: seg) {
            que.push_back(it[0]);
            que.push_back(it[1]);
        }
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int n = que.size();
        vector<int> ctr(n), sum(n);
        for(auto &it: seg) {
            int L = lower_bound(que.begin(), que.end(), it[0]) - que.begin();
            int R = lower_bound(que.begin(), que.end(), it[1]) - que.begin();
            ++ctr[L];
            --ctr[R];
            sum[L] += it[2];
            sum[R] -= it[2];
        }
        vector<vector<int> > ret;
        --n;
        for(int i = 0, j; i < n; i = j) {
            int avg = sum[i] / max(ctr[i], 1);
            for(j = i + 1; j < n; ++j) {
                sum[j] += sum[j - 1];
                ctr[j] += ctr[j - 1];
                if(avg != sum[j] / max(ctr[j], 1))
                    break;
            }
            if(avg > 0)
                ret.push_back({que[i], que[j], avg});
        }
        return ret;
    }
};
