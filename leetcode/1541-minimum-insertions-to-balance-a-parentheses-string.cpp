class Solution {
public:
    int minInsertions(string s) {
        int n = (int)s.size(), sum = 0, his = 0, adt = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '(') {
                ++sum;
            } else {
                if(i + 1 < n && s[i + 1] == ')') {
                    ++i;
                } else {
                    ++adt;
                }
                --sum;
            }
            his = min(his, sum);
        }
        return abs(his) + (sum - his) * 2 + adt;
    }
};
