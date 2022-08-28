class Solution {
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        const int maxd = 26;
        int ctr[maxd] = {};
        for(char ch: word1)
            ++ctr[(int)(ch - 'a')];
        for(char ch: word2)
            --ctr[(int)(ch - 'a')];
        for(int i = 0; i < maxd; ++i)
            if(abs(ctr[i]) > 3)
                return false;
        return true;
    }
};
