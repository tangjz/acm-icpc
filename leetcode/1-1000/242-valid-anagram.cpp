class Solution {
public:
    bool isAnagram(string s, string t) {
        const int maxd = 26;
        vector<int> ctr(maxd);
        for(char c: s)
            ++ctr[(int)(c - 'a')];
        for(char c: t)
            --ctr[(int)(c - 'a')];
        for(int i = 0; i < maxd; ++i)
            if(ctr[i])
                return false;
        return true;
    }
};
