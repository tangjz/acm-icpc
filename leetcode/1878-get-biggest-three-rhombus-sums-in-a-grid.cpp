class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        const int d[2][2] = {{-1, 1}, {1, 1}};
        int n = grid.size(), m = grid[0].size();
        vector<int> best(3, INT_MIN);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int pos[4][2] = {{i, j}, {i, j}, {i, j}, {i, j}};
                bool bad = false;
                for(int k = 1; !bad; ++k) {
                    int sum = 0;
                    if(k == 1) {
                        sum += grid[pos[0][0]][pos[0][1]];
                    } else {
                        for(int x = pos[0][0], y = pos[0][1]; !(x == pos[1][0] && y == pos[1][1]); ) {
                            sum += grid[x][y];
                            x += d[0][0];
                            y += d[0][1];
                        }
                        for(int x = pos[1][0], y = pos[1][1]; !(x == pos[3][0] && y == pos[3][1]); ) {
                            sum += grid[x][y];
                            x += d[1][0];
                            y += d[1][1];
                        }
                        for(int x = pos[0][0], y = pos[0][1]; !(x == pos[2][0] && y == pos[2][1]); ) {
                            x += d[1][0];
                            y += d[1][1];
                            sum += grid[x][y];
                        }
                        for(int x = pos[2][0], y = pos[2][1]; !(x == pos[3][0] && y == pos[3][1]); ) {
                            x += d[0][0];
                            y += d[0][1];
                            sum += grid[x][y];
                        }
                    }
                    // printf("(%d, %d) %d: %d\n", i, j, k, sum);
                    for(int o = 0; o < 3; ++o) {
                        if(sum == best[o])
                            break;
                        if(sum > best[o])
                            swap(sum, best[o]);
                    }
                    // printf("%d %d %d (%d)\n", best[0], best[1], best[2], sum);
                    for(int o = 1; o < 4; ++o) {
                        if(o & 1) {
                            pos[o][0] += d[0][0];
                            pos[o][1] += d[0][1];
                        }
                        if(o & 2) {
                            pos[o][0] += d[1][0];
                            pos[o][1] += d[1][1];
                        }
                        bad |= pos[o][0] < 0 || pos[o][0] >= n || pos[o][1] < 0 || pos[o][1] >= m;
                    }
                }
            }
        while(!best.empty() && best.back() == INT_MIN)
            best.pop_back();
        return best;
    }
};
