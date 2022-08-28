class Solution {
public:
    string smallestGoodBase(string n) {
        typedef long long LL;
        LL v = stol(n);
        for(LL base = 2; base * base * base + base * base + base + 1 <= v; ++base) {
            bool ban = 0;
            for(LL tp = v; !ban && tp > 0; ban |= tp % base != 1, tp /= base);
            if(!ban)
                return to_string(base);
        }
        LL base = max((LL)floor(sqrtl(v - 0.75) - 0.5), 2LL);
        for( ; base * base + base + 1 < v; ++base);
        if(base * base + base + 1 == v)
            return to_string(base);
        return to_string(v - 1);
    }
};
