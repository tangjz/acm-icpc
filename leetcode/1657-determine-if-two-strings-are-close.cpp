class Solution {
public:
    bool closeStrings(string word1, string word2) {
        const int maxc = 26;
        vector<int> ctr1(maxc), ctr2(maxc);
        for(char ch: word1)
            ++ctr1[(int)(ch - 'a')];
        for(char ch: word2)
            ++ctr2[(int)(ch - 'a')];
        for(int i = 0; i < maxc; ++i)
            if(!!ctr1[i] != !!ctr2[i])
                return false;
        sort(ctr1.begin(), ctr1.end());
        sort(ctr2.begin(), ctr2.end());
        return ctr1 == ctr2;
    }
};
