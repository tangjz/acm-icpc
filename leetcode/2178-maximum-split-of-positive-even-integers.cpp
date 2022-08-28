class Solution {
public:
    vector<long long> maximumEvenSplit(long long s) {
        if(s & 1)
            return {};
        typedef long long LL;
        vector<LL> ret;
        for(LL i = 2; i <= s; i += 2) {
            s -= i;
            ret.push_back(i);
        }
        ret.back() += s;
        return ret;
    }
};
