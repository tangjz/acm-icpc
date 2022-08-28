class Solution {
public:
    string makeGood(string s) {
        string t = "";
        for(char ch : s)
            if(!t.empty() && t.back() != ch && tolower(t.back()) == tolower(ch)) {
                t.pop_back();
            } else {
                t.push_back(ch);
            }
        return t;
    }
};
