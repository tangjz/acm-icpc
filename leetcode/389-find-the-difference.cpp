class Solution {
public:
    char findTheDifference(string s, string t) {
        unordered_map<char, int> ctr;
        for(char ch : t)
            ++ctr[ch];
        for(char ch : s)
            if(!(--ctr[ch]))
                ctr.erase(ch);
        return ctr.begin() -> first;
    }
};
