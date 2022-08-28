class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int n = (int)seats.size(), m = (int)seats[0].size(), all = 1 << n;
        vector<int> f(all, 0);
        for(int i = 0; i < m; ++i) {
            vector<int> g(all, 0);
            for(int j = 1; j < all; j <<= 1)
                for(int k = 0; k < all; ++k)
                    if(j & k)
                        f[k] = max(f[k], f[k ^ j]);
            int msk = 0;
            for(int j = 0; j < n; ++j)
                if(seats[j][i] == '.')
                    msk |= 1 << j;
            for(int rem = 0; rem <= msk; ++rem) {
                if((rem & msk) != rem)
                    continue;
                g[rem] += f[~(rem << 1 | rem | rem >> 1) & (all - 1)];
                for(int j = 0; j < n; ++j)
                    g[rem] += (rem >> j) & 1;
            }
            f = move(g);
        }
        return *max_element(f.begin(), f.end());
    }
};
