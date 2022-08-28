class Solution {
public:
    string maxValue(string n, int x) {
        bool neg = n[0] == '-';
        int pos = neg, len = (int)n.length();
        n.push_back('0' + x);
        for( ; pos < len; ++pos)
            if(n[pos] != n.back() && (n[pos] > n.back()) == neg) {
                rotate(n.begin() + pos, n.begin() + len, n.begin() + len + 1);
                break;
            }
        return n;
    }
};
