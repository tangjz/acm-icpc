class Solution {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        auto toInt = [&](string tim) {
            int hh = (tim[0] - '0') * 10 + (tim[1] - '0');
            int mm = (tim[3] - '0') * 10 + (tim[4] - '0');
            return hh * 60 + mm;
        };
        int pL = toInt(event1[0]), pR = toInt(event1[1]);
        int qL = toInt(event2[0]), qR = toInt(event2[1]);
        return max(pL, qL) <= min(pR, qR);
    }
};
