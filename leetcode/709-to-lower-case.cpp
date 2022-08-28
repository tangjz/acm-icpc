class Solution {
public:
    string toLowerCase(string s) {
        for(char &ch: s)
            ch = tolower(ch);
        return move(s);
    }
};
