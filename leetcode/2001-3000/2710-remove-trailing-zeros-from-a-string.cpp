class Solution {
public:
    string removeTrailingZeros(string s) {
        while(s.back() == '0')
            s.pop_back();
        return s;
    }
};
