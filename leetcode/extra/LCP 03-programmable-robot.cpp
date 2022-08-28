class Solution {
public:
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        int n = command.size(), dx = 0, dy = 0;
        map<pair<int, int>, int> Hash;
        for(int i = 0; i < n; ++i) {
            Hash[{dx, dy}] = i;
            (command[i] == 'R' ? dx : dy) += 1;
        }
        assert(dx > 0 && dy > 0);
        auto calc = [&](int x, int y) -> pair<int, int> {
            int fir = min(x / dx, y / dy);
            auto it = Hash.find({x - fir * dx, y - fir * dy});
            if(it == Hash.end())
                return {-1, -1};
            return {fir, it -> second};
        };
        pair<int, int> u = calc(x, y), v;
        if(u.first == -1)
            return 0;
        for(auto &it: obstacles) {
            v = calc(it[0], it[1]);
            if(v.first != -1 && v <= u)
                return 0;
        }
        return 1;
    }
};
