class Solution {
    typedef long long LL;
    int getPrev(int x) {
        int p = x & -x;
        if(p > 1)
            return x ^ p ^ (p >> 1);
        LL y = x + 1LL;
        x &= y;
        p = x & -x;
        return !p ? -1 : x - ((p / (y & -y)) >> 1);
    }
    int getNext(int x) {
        int p = x & -x;
        LL y = (LL)x + p;
        y |= ((x & ~y) / p) >> 1;
        return y > INT_MAX ? -1 : y;
    }
public:
    vector<int> findClosedNumbers(int num) {
        return {getNext(num), getPrev(num)};
    }
};
