class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        typedef long long LL;
        LL x = numerator, y = denominator;
        if(y < 0) {
            x = -x;
            y = -y;
        }
        string ret = "";
        if(x < 0) {
            ret.push_back('-');
            x = -x;
        }
        ret += to_string(x / y);
        if(!(x %= y))
            return ret;
        ret.push_back('.');
        unordered_map<LL, int> pos;
        for(int i = ret.size(); x > 0; ++i) {
            auto it = pos.find(x);
            if(it != pos.end()) {
                ret.push_back('(');
                rotate(ret.begin() + (it -> second), ret.end() - 1, ret.end());
                ret.push_back(')');
                break;
            }
            pos[x] = i;
            x *= 10;
            ret.push_back('0' + (x / y));
            x %= y;
        }
        return ret;
    }
};
