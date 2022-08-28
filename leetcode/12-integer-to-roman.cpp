class Solution {
public:
    string intToRoman(int num) {
        const pair<int, char> magnitude[] = {{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};
        string ret;
        for(int i = 6; i >= 0; --i) {
            int j = i > 0 ? ((i - 1) >> 1) << 1 : -1;
            int hi = num / magnitude[i].first;
            bool adt = 0;
            if(j >= 0 && (num + magnitude[j].first) / magnitude[i].first > hi) {
                adt = 1;
                num += magnitude[j].first;
                ++hi;
            }
            while(hi > 0) {
                if(adt && hi == 1)
                    ret.push_back(magnitude[j].second);
                ret.push_back(magnitude[i].second);
                --hi;
                num -= magnitude[i].first;
            }
        }
        return ret;
    }
};
