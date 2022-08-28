class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<char> vowel = {'a', 'e', 'i', 'o', 'u'};
        unordered_set<string> h1;
        unordered_map<string, string> h2, h3;
        vector<string> ret;
        for(auto &it: wordlist) {
            h1.insert(it);
            string rep = it;
            for(char &ch: rep)
                ch = tolower(ch);
            if(!h2.count(rep))
                h2[rep] = it;
            for(char &ch: rep)
                if(vowel.count(ch))
                    ch = '.';
            if(!h3.count(rep))
                h3[rep] = it;
        }
        for(auto &it: queries) {
            if(h1.count(it)) {
                ret.push_back(it);
                continue;
            }
            for(char &ch: it)
                ch = tolower(ch);
            if(h2.count(it)) {
                ret.push_back(h2[it]);
                continue;
            }
            for(char &ch: it)
                if(vowel.count(ch))
                    ch = '.';
            if(h3.count(it)) {
                ret.push_back(h3[it]);
            } else {
                ret.push_back("");
            }
        }
        return ret;
    }
};
