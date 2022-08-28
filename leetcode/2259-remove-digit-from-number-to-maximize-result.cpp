class Solution {
public:
    string removeDigit(string number, char digit) {
        int n = number.size(), las = -1, pos = -1;
        for(int i = 0; i < n; ++i) {
            char ch = number[i];
            if(ch != digit)
                continue;
            las = i;
            if(i + 1 < n && ch < number[i + 1]) {
                pos = i;
                break;
            }
        }
        if(pos == -1)
            pos = las;
        rotate(number.begin() + pos, number.begin() + pos + 1, number.end());
        number.pop_back();
        return number;
    }
};
