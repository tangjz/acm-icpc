class Solution {
public:
    vector<int> distributeCandies(int m, int n) {
        vector<int> ret(n);
        for(int i = 1; m > 0; ++i) {
            int j = (i - 1) % n, k = min(i, m);
            ret[j] += k;
            m -= k;
        }
        return ret;
    }
};
