class Solution {
public:
    vector<string> cellsInRange(string s) {
        vector<string> ret;
        for(char x = s[0]; x <= s[3]; ++x)
            for(char y = s[1]; y <= s[4]; ++y) {
                string t = "";
                t += x;
                t += y;
                ret.push_back(t);
            }
        return ret;
    }
};
