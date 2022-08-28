class Solution {
public:
    string removeOuterParentheses(string s) {
        int c = 0;
        string t = "";
        for(char ch: s)
            if(ch == '(') {
                if(c > 0)
                    t.push_back(ch);
                ++c;
            } else {
                --c;
                if(c > 0)
                    t.push_back(ch);
            }
        return t;
    }
};
