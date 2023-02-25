class Solution {
public:
    int findCrossingTime(int m, int n, vector<vector<int>>& time) {
        vector<pair<int, int> > key(n);
        for(int i = 0; i < n; ++i)
            key[i] = {time[i][0] + time[i][2], i};
        vector<int> ord(n), rnk(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return key[u] < key[v];
        });
        int ans = 0, cur = 0;
        priority_queue<pair<int, int> > lft, mid, rht, end; // (pri, idx), (-tim, idx), (pri, idx), (-tim, idx)
        for(int i = 0; i < n; ++i) {
            printf("push %d %d\n", i, ord[i]);
            lft.push({i, ord[i]});
            rnk[ord[i]] = i;
        }
        while(m > 0) {
            printf("cur: %d\n", cur);
            for( ; !end.empty() && -end.top().first <= cur; ) {
                int u = end.top().second;
                end.pop();
                lft.push({rnk[u], u});
            }
            for( ; !mid.empty() && -mid.top().first <= cur; ) {
                int u = mid.top().second;
                mid.pop();
                rht.push({rnk[u], u});
            }
            if(!rht.empty()) {
                int u = rht.top().second;
                printf("rht: %d\n", u);
                rht.pop();
                cur += time[u][2];
                ans = max(ans, cur);
                --m;
                end.push({-(cur + time[u][3]), u});
            } else if(!lft.empty() && m > mid.size()) {
                int u = lft.top().second;
                printf("lft: %d\n", u);
                lft.pop();
                cur += time[u][0];
                mid.push({-(cur + time[u][1]), u});
            } else {
                assert(mid.size() + end.size() > 0);
                int low = INT_MAX;
                if(!mid.empty())
                    low = min(low, -mid.top().first);
                if(!end.empty())
                    low = min(low, -end.top().first);
                cur = max(cur, low);
            }
        }
        return ans;
    }
};
