class Solution {
public:
    string removeVowels(string s) {
        unordered_set vowel = {'a', 'e', 'i', 'o', 'u'};
        int tot = 0;
        for(char ch: s) {
            if(vowel.count(ch))
                continue;
            s[tot++] = ch;
        }
        s.resize(tot);
        return s;
    }
};
