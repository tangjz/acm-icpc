class Solution {
public:
    int smallestValue(int n) {
        auto F = [&](int x) {
            int ret = 0;
            for(int i = 2; i <= x; ++i) {
                if(i * i > x)
                    i = x;
                for( ; x % i == 0; x /= i, ret += i);
            }
            return ret;
        };
        for(int m; (m = F(n)) < n; n = m);
        return n;
    }
};
