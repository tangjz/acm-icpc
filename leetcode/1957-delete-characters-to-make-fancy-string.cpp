class Solution {
public:
    string makeFancyString(string s) {
        string t = "";
        bool eq = 0;
        for(char ch: s) {
            if(ch != t.back()) {
                t.push_back(ch);
                eq = 0;
                continue;
            }
            if(eq)
                continue;
            t.push_back(ch);
            eq = 1;
        }
        return t;
    }
};
