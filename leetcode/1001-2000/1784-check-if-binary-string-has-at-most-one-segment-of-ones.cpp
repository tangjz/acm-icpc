class Solution {
public:
    bool checkOnesSegment(string s) {
        auto L = s.find('1');
        if(L == string::npos)
            return 1;
        auto R = s.rfind('1');
        for(int i = L + 1; i < R; ++i)
            if(s[i] != '1')
                return 0;
        return 1;
    }
};
