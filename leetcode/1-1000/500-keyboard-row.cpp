class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        const string rows[] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        unordered_map<char, int> mp;
        for(int i = 0; i < 3; ++i)
            for(char ch: rows[i])
                mp[ch] = 1 << i;
        vector<string> ret;
        for(auto &word: words) {
            int msk = 0;
            for(char ch: word)
                msk |= mp[tolower(ch)];
            if(msk & (msk - 1))
                continue;
            ret.push_back(word);
        }
        return ret;
    }
};
