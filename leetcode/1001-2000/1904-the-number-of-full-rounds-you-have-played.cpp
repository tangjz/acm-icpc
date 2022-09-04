class Solution {
public:
    int numberOfRounds(string A, string B) {
        auto toInt = [&](string const &s) {
            int hh, mm;
            sscanf(s.c_str(), "%d:%d", &hh, &mm);
            return hh * 60 + mm;
        };
        int s = toInt(A), t = toInt(B);
        if(s > t)
            t += 1440;
        return max(t / 15 - (s + 14) / 15, 0);
    }
};
