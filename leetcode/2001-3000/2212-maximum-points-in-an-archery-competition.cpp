class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        const int maxd = 12;
        pair<int, int> best = {0, 0};
        for(int i = 0; i < (1 << maxd); ++i) {
            int low = 0, sum = 0;
            for(int j = 0; j < maxd; ++j)
                if((i >> j) & 1) {
                    low += aliceArrows[j] + 1;
                    sum += j;
                }
            if(low > numArrows)
                continue;
            best = max(best, make_pair(sum, i));
        }
        int rem = numArrows;
        vector<int> ret(maxd);
        for(int i = 0; i < maxd; ++i)
            if((best.second >> i) & 1) {
                ret[i] = aliceArrows[i] + 1;
                rem -= aliceArrows[i] + 1;
            }
        ret[0] += rem;
        return ret;
    }
};
