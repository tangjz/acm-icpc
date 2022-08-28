class Solution {
public:
    int countVowelSubstrings(string word) {
        const char *pat = "aeiou";
        int n = word.length(), ctr = 0;
        for(int i = 0; i < n; ++i) {
            int msk = 0;
            for(int j = i; j < n; ++j) {
                int k;
                for(k = 0; k < 5; ++k)
                    if(word[j] == pat[k])
                        break;
                msk |= 1 << k;
                if(msk >= 32)
                    break;
                ctr += msk == 31;
            }
        }
        return ctr;
    }
};
