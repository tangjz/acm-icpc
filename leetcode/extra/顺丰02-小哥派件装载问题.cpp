class Solution {
public:
    int minRemainingSpace(vector<int>& N, int V) {
        static const int maxv = 2001;
        static bitset<maxv> dp;
        dp.reset();
        dp.set(0);
        for(int x: N)
            dp |= dp << x;
        for(int i = V; i >= 0; --i)
            if(dp.test(i))
                return V - i;
        return -1;
    }
};
