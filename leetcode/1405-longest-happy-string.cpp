class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        int rem[3] = {a, b, c}, ord[3] = {0, 1, 2};
        string ret = "";
        while(1) {
            sort(ord, ord + 3, [&](int const &u, int const &v) {
                return rem[u] > rem[v];
            });
            if(!rem[ord[0]])
                break;
            int pos = ord[0];
            char ch = 'a' + pos;
            if(ret.length() > 1 && ret.back() == ch && ret[ret.length() - 2] == ch) {
                if(!rem[ord[1]])
                    break;
                pos = ord[1];
                ch = 'a' + pos;
            }
            ret += ch;
            --rem[pos];
        }
        return ret;
    }
};
