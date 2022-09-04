class Solution {
    int toNum(string &pat) {
        static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int mm = stoi(pat.substr(0, 2));
        int ans = stoi(pat.substr(3));
        for(int i = 1; i < mm; ++i)
            ans += days[i];
        return ans;
    }
public:
    int countDaysTogether(string a, string b, string c, string d) {
        return max(min(toNum(b), toNum(d)) - max(toNum(a), toNum(c)) + 1, 0);
    }
};
