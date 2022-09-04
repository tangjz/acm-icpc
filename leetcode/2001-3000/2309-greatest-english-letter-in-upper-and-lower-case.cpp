class Solution {
public:
    string greatestLetter(string s) {
        unordered_map<char, int> msk;
        for(char ch: s)
            if(islower(ch)) {
                msk[toupper(ch)] |= 2;
            } else {
                msk[ch] |= 1;
            }
        char best = '\0';
        for(auto &it: msk)
            if(it.second == 3)
                best = max(best, it.first);
        string ret;
        if(best)
            ret.push_back(best);
        return ret;
    }
};
