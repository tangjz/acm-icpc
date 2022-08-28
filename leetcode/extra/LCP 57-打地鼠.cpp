class Solution {
public:
    int getMaximumNumber(vector<vector<int>>& moles) {
        vector<pair<int, int> > best[3][3];
        sort(moles.begin(), moles.end());
        for(auto &it: moles) {
            int cur = -1, ct = it[0], cx = it[1], cy = it[2];
            if(abs(cx - 1) + abs(cy - 1) <= ct)
                cur = 0;
            for(int px = 0; px < 3; ++px)
                for(int py = 0; py < 3; ++py) {
                    if(best[px][py].empty())
                        continue;
                    int upp = ct - abs(cx - px) - abs(cy - py);
                    for(int i = best[px][py].size() - 1; i >= 0; --i) {
                        if(best[px][py][i].first > upp)
                            continue;
                        cur = max(cur, best[px][py][i].second);
                        break;
                    }
                }
            if(cur == -1)
                continue;
            ++cur;
            if(!best[cx][cy].empty())
                cur = max(cur, best[cx][cy].back().second);
            best[cx][cy].push_back({ct, cur});
        }
        int ans = 0;
        for(int x = 0; x < 3; ++x)
            for(int y = 0; y < 3; ++y)
                if(!best[x][y].empty())
                    ans = max(ans, best[x][y].back().second);
        return ans;
    }
};
