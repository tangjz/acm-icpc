class Solution {
public:
    bool isAcronym(vector<string>& words, string s) {
        string t = "";
        for(auto &it: words)
            t.push_back(it.front());
        return s == t;
    }
};
