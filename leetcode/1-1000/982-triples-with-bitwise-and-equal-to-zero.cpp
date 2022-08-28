class Solution {
public:
    int countTriplets(vector<int>& nums) {
        int mx = 0;
        vector<int> f = {0};
        for(int x: nums) {
            for( ; (1 << mx) <= x; f.resize(1 << (++mx)));
            ++f[x];
        }
        int m = 1 << mx;
        for(int i = 1; i < m; i <<= 1)
            for(int j = 0; j < m; ++j)
                if(i & j)
                    f[j ^ i] += f[j];
        for(int i = 0; i < m; ++i)
            f[i] = f[i] * f[i] * f[i];
        for(int i = 1; i < m; i <<= 1)
            for(int j = 0; j < m; ++j)
                if(i & j)
                    f[j ^ i] -= f[j];
        return f[0];
    }
};
