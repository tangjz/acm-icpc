class Solution {
public:
    vector<vector<int>> findContinuousSequence(int n) {
        int even = 2;
        vector<vector<int> > ret;
        auto gen = [&](int x, int y) {
            if(x < y)
                swap(x, y);
            if(y == 1)
                return;
            int R = (x + y - 1) >> 1, L = x - R;
            vector<int> row(y);
            iota(row.begin(), row.end(), L);
            ret.emplace_back(row);
        };
        for( ; !(n & 1); n >>= 1, even <<= 1);
        for(int i = 1; i * i <= n; ++i) {
            if(n % i > 0)
                continue;
            gen(i * even, n / i);
            if(i * i < n)
                gen(n / i * even, i);
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
};
