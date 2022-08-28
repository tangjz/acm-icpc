class Solution {
public:
    int circleGame(vector<vector<int>>& toys, vector<vector<int>>& circles, int r) {
        unordered_map<int, vector<pair<int, int> > > sp;
        for(auto &it: toys)
            sp[it[0]].push_back({it[1], 0});
        for(auto &it: sp) {
            auto &vec = it.second;
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
        }
        vector<vector<int> > dis;
        for(int x = 0; x < r; ++x) {
            vector<int> row;
            for(int y = 0, d = 0; y < r; ++y) {
                int v = x * x + y * y;
                for( ; d * d < v; ++d);
                if(d >= r)
                    break;
                row.push_back(d);
            }
            dis.push_back(move(row));
        }
        sort(circles.begin(), circles.end());
        circles.erase(unique(circles.begin(), circles.end()), circles.end());
        for(auto &it: circles)
            for(int x = it[0] - r + 1; x < it[0] + r; ++x) {
                auto jt = sp.find(x);
                if(jt == sp.end())
                    continue;
                int dx = abs(x - it[0]), dy = dis[dx].size() - 1;
                int yL = it[1] - dy, yR = it[1] + dy;
                auto &vec = jt -> second;
                auto kt = lower_bound(vec.begin(), vec.end(), make_pair(yL, 0));
                for( ; kt != vec.end() && kt -> first <= yR; ++kt) {
                    dy = abs(kt -> first - it[1]);
                    kt -> second = max(kt -> second, r - dis[dx][dy]);
                }
            }
        int ans = 0;
        for(auto &it: toys) {
            auto &vec = sp[it[0]];
            auto jt = lower_bound(vec.begin(), vec.end(), make_pair(it[1], 0));
            assert(jt != vec.end() && jt -> first == it[1]);
            ans += it[2] <= jt -> second;
        }
        return ans;
    }
};
