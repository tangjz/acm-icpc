class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        const int maxv = 70 * 70 + 1;
        bitset<maxv> ret, tmp;
        ret.reset();
        ret.set(0);
        for(auto &row: mat) {
            tmp = ret;
            ret.reset();
            for(int x: row)
                ret |= tmp << x;
        }
        for(int i = 0; i <= target || target + i < maxv; ++i) {
            if(i <= target && ret.test(target - i))
                return i;
            if(target + i < maxv && ret.test(target + i))
                return i;
        }
        return maxv;
    }
};
