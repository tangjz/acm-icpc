class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& seg) {
        typedef long long LL;
        int m = seg.size();
        vector<int> ctr(n);
        LL pos = 0;
        set<int> cand;
        for(int i = 0; i < n; ++i)
            cand.insert(i);
        priority_queue<pair<LL, int> > que;
        sort(seg.begin(), seg.end());
        for(auto &it: seg) {
            pos = max(pos, (LL)it[0]);
            while(!que.empty() && -que.top().first <= pos) {
                // printf("freeze %lld %d\n", pos, que.top().second);
                cand.insert(que.top().second);
                que.pop();
            }
            if(cand.empty()) {
                pos = max(pos, -que.top().first);
                // printf("freeze %lld %d\n", pos, que.top().second);
                cand.insert(que.top().second);
                que.pop();
                while(!que.empty() && -que.top().first <= pos) {
                    // printf("freeze %lld %d\n", pos, que.top().second);
                    cand.insert(que.top().second);
                    que.pop();
                }
            }
            int j = *cand.begin();
            cand.erase(j);
            // printf("tim %lld pos %d seg %d %d => freeze %lld\n", pos, j, it[0], it[1], pos + it[1] - it[0]);
            ++ctr[j];
            que.push({-(pos + it[1] - it[0]), j});
        }
        pos = 0;
        for(int i = 1; i < n; ++i)
            if(ctr[pos] < ctr[i])
                pos = i;
        return pos;
    }
};
