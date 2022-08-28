class Solution {
public:
    int visibleMountains(vector<vector<int>>& peaks) {
        int n = peaks.size();
        vector<int> que;
        que.reserve(n);
        for(auto &it: peaks) {
            tie(it[0], it[1]) = make_pair(-it[0] - it[1], it[0] - it[1]);
            que.push_back(it[1]);
        }
        sort(peaks.begin(), peaks.end());
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> bits(m);
        vector<bool> ban(n);
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && peaks[i] == peaks[j]; ++i);
            int cnt = 0, pos = lower_bound(que.begin(), que.end(), peaks[j][1]) - que.begin();
            if(i - j > 1) {
                cnt = 1;
            } else {
                for(int x = pos + 1; x > 0; x -= x & -x)
                    cnt += bits[x - 1];
            }
            for(int x = pos + 1; x <= m; x += x & -x)
                bits[x - 1] += i - j;
            for( ; j < i; ++j)
                ban[j] = cnt;
        }
        int ans = 0;
        for(bool x: ban)
            ans += !x;
        return ans;
    }
};
