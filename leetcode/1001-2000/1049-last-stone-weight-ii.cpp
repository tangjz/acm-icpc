class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        const int maxv = 3001;
        int tot = 0;
        bitset<maxv> msk;
        msk.reset();
        msk.set(0);
        for(int x: stones) {
            tot += x;
            msk |= msk << x;
        }
        int ans = tot;
        for(int i = 1; i < tot; ++i)
            if(msk.test(i)) {
                ans = min(ans, abs(tot - i - i));
            }
        return ans;
    }
};
