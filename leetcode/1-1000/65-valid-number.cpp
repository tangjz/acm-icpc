class Solution {
public:
    bool isNumber(string_view s) {
        auto isInteger = [&](string_view s, bool allowSign) -> bool {
            if(allowSign && !s.empty() && (s[0] == '-' || s[0] == '+'))
                s = s.substr(1);
            for(char ch: s)
                if(!isdigit(ch))
                    return 0;
            return !s.empty();
        };
        auto isDecimal = [&](string_view s) -> bool {
            auto u = s.find('.');
            if(u == string::npos)
                return isInteger(s, 1);
            auto v = s.find('.', u + 1);
            if(v != string::npos)
                return 0;
            if(s[0] == '-' || s[0] == '+') {
                s = s.substr(1);
                --u;
            }
            if(s.size() == 1)
                return 0;
            return (!u || isInteger(s.substr(0, u), 0)) && (u + 1 == s.size() || isInteger(s.substr(u + 1), 0));
        };
        int L = 0, R = s.size();
        for( ; L < R && s[L] == ' '; ++L);
        for( ; L < R && s[R - 1] == ' '; --R);
        s = s.substr(L, R - L);
        auto u = s.find('e'), v = s.find('E');
        int c0 = u != string::npos, c1 = v != string::npos;
        if(c0 != c1) {
            if(c0) {
                c0 += s.find('e', u + 1) != string::npos;
            } else {
                c1 += s.find('E', v + 1) != string::npos;
            }
        }
        if(c0 + c1 > 1)
            return 0;
        if(!c0 && !c1)
            return isDecimal(s);
        if(c1)
            u = v;
        return isDecimal(s.substr(0, u)) && isInteger(s.substr(u + 1), 1);
    }
};
