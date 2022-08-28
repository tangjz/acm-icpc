class Solution {
public:
    string maximumTime(string time) {
        for(int i = 1439; i >= 0; --i) {
            int hh = i / 60, mm = i % 60;
            string ret = to_string(hh / 10) + to_string(hh % 10) + ":" + to_string(mm / 10) + to_string(mm % 10);
            bool bad = false;
            for(int j = 0; !bad && j < 5; ++j)
                bad |= time[j] != '?' && time[j] != ret[j];
            if(!bad)
                return ret;
        }
        return "";
    }
};
