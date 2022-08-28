class Solution {
public:
    string nextClosestTime(string time) {
        static const int maxn = 1440, maxs = 1 << 10 | 1;
        static int init = 0, rep[maxn + 1] = {};
        if(!init) {
            for(int i = 0; i < maxn; ++i) {
                int hh = i / 60, mm = i % 60;
                rep[i] = 1 << (hh % 10) | 1 << (hh / 10) | 1 << (mm / 10) | 1 << (mm % 10);
            }
            init = 1;
        }
        int cur = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3)), upp = rep[cur];
        do (++cur) == maxn && (cur = 0); while((rep[cur] & upp) != rep[cur]);
        static char buf[7];
        sprintf(buf, "%02d:%02d", cur / 60, cur % 60);
        return buf;
    }
};
