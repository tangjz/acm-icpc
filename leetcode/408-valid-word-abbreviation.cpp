class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int n = word.size(), m = abbr.size(), j = 0;
        for(int i = 0; i < m; )
            if(abbr[i] >= '0' && abbr[i] <= '9') {
                int val = 0;
                if(abbr[i] == '0')
                    return 0;
                for( ; i < m && abbr[i] >= '0' && abbr[i] <= '9'; val = val * 10 + (abbr[i++] - '0'));
                if((j += val) > n)
                    return 0;
            } else if(abbr[i++] != (j < n ? word[j++] : '\0')) {
                return 0;
            }
        return j == n;
    }
};
