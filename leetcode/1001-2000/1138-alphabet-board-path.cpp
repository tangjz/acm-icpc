class Solution {
public:
    string alphabetBoardPath(string target) {
        string ret = "";
        int x = 0, y = 0;
        for(char ch: target) {
            int o = ch - 'a';
            int tx = o / 5, ty = o % 5;
            if(x == 5 && x > tx) {
                --x;
                ret.push_back('U');
            }
            for( ; y < ty; ++y, ret.push_back('R'));
            for( ; y > ty; --y, ret.push_back('L'));
            for( ; x < tx; ++x, ret.push_back('D'));
            for( ; x > tx; --x, ret.push_back('U'));
            ret.push_back('!');
        }
        return ret;
    }
};
