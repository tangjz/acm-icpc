class Solution {
public:
    vector<int> bestLine(vector<vector<int>>& points) {
        typedef long long LL;
        int n = (int)points.size();
        pair<int, pair<int, int> > ans = {0, {-1, -1}};
        for(int i = 0; i < n; ++i) {
            pair<int, int> cnt = {0, -n}, upp = {0, -n};
            map<pair<LL, LL>, pair<int, int> > Hash;
            for(int j = 0; j < n; ++j) {
                LL dx = (LL)points[i][0] - points[j][0], dy = (LL)points[i][1] - points[j][1];
                if(!dx && !dy) {
                    ++cnt.first;
                    cnt.second = max(cnt.second, -j);
                    continue;
                }
                LL com = __gcd(dx, dy);
                auto &it = Hash[make_pair(dx / com, dy / com)];
                if(!it.first)
                    it.second = -n;
                ++it.first;
                it.second = max(it.second, -j);
                upp = max(upp, it);
            }
            cnt.first += upp.first;
            upp = {cnt.second, upp.second};
            if(upp.first < upp.second)
                swap(upp.first, upp.second);
            ans = max(ans, make_pair(cnt.first, upp));
        }
        return {-ans.second.first, -ans.second.second};
    }
};
