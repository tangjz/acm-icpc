class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        int ans = INT_MAX;
        for(int i = targetSeconds % 60; i < 100; i += 60) {
            int j = (targetSeconds - i) / 60;
            if(j >= 100)
                continue;
            bool fir = 1;
            string buf = "";
            buf += '0' + startAt;
            buf += '0' + (j / 10) % 10;
            if(fir && buf.back() == '0') {
                buf.pop_back();
            } else {
                fir = 0;
            }
            buf += '0' + j % 10;
            if(fir && buf.back() == '0') {
                buf.pop_back();
            } else {
                fir = 0;
            }
            buf += '0' + (i / 10) % 10;
            if(fir && buf.back() == '0') {
                buf.pop_back();
            } else {
                fir = 0;
            }
            buf += '0' + i % 10;
            if(fir && buf.back() == '0') {
                buf.pop_back();
            } else {
                fir = 0;
            }
            int tmp = 0;
            for(int k = 1; k < (int)buf.size(); ++k) {
                tmp += moveCost * (buf[k - 1] != buf[k]);
                tmp += pushCost;
            }
            ans = min(ans, tmp);
        }
        return ans;
    }
};
