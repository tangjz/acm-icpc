class Solution {
public:
    int convertTime(string current, string correct) {
        auto toInt = [&](string const &s) {
            int hh, mm;
            sscanf(s.c_str(), "%d:%d", &hh, &mm);
            return hh * 60 + mm;
        };
        int dt = abs(toInt(current) - toInt(correct));
        int ans = dt / 60;
        dt %= 60;
        ans += dt / 15;
        dt %= 15;
        ans += dt / 5;
        dt %= 5;
        ans += dt;
        return ans;
    }
};
