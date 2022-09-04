class Solution {
public:
    bool areOccurrencesEqual(string s) {
        unordered_map<char, int> ctr;
        for(char ch: s)
            ++ctr[ch];
        int val = ctr.begin() -> second;
        for(auto &it: ctr)
            if(it.second != val)
                return 0;
        return 1;
    }
};
