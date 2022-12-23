class Solution {
public:
    int countTime(string time) {
        static vector<string> cand;
        int ret = 0;
        if(cand.empty()) {
            for(int i = 0; i < 1440; ++i) {
                int hh = i / 60, mm = i % 60;
                static char buf[7];
                sprintf(buf, "%02d:%02d", hh, mm);
                cand.push_back((string)buf);
            }
        }
        for(auto &it: cand) {
            int pos = 0;
            for( ; pos < 5 && (time[pos] == '?' || time[pos] == it[pos]); ++pos);
            ret += pos == 5;
        }
        return ret;
    }
};
