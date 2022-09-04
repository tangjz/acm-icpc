class Solution {
public:
    int dayOfYear(string date) {
        static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int yy, mm, dd;
        sscanf(date.c_str(), "%d-%d-%d", &yy, &mm, &dd);
        int ans = dd;
        for(int i = 1; i < mm; ++i)
            ans += days[i];
        if(mm > 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
            ++ans;
        return ans;
    }
};
