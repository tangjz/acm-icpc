class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        map<int, vector<char> > vis;
        for(auto &it : reservedSeats) {
            vis[it[0] - 1].resize(10);
            vis[it[0] - 1][it[1] - 1] = 1;
        }
        int ans = (n - (int)vis.size()) * 2;
        for(auto &it : vis) {
            auto &row = it.second;
            auto check = [&](int L, int R) {
                for(int j = L; j < R; ++j)
                    if(row[j])
                        return 0;
                return 1;
            };
            for(int j = 1; j < 6; j += 2)
                if(check(j, j + 4)) {
                    ++ans;
                    if(j == 1 && check(j + 4, j + 8))
                        ++ans;
                    break;
                }
        }
        return ans;
    }
};
