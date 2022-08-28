class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        static const int maxh = 4, maxm = 6;
        static vector<vector<int> > hh(maxh + 1), mm(maxm + 1);
        if(hh[0].empty()) {
            for(int i = 0; i < 12; ++i)
                hh[__builtin_popcount(i)].push_back(i);
            for(int i = 0; i < 60; ++i)
                mm[__builtin_popcount(i)].push_back(i);
        }
        vector<string> ret;
        for(int i = 0; i <= maxh && i <= turnedOn; ++i) {
            int j = turnedOn - i;
            if(j < 0 || j > maxm)
                continue;
            for(int h: hh[i])
                for(int m: mm[j]) {
                    static char buf[7];
                    sprintf(buf, "%d:%02d", h, m);
                    ret.push_back(buf);
                }
        }
        return ret;
    }
};
