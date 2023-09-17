class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        int n = words.size(), m = 26;
        string rnk;
        rnk.resize(m);
        for(int i = 0; i < m; ++i)
            rnk[order[i] - 'a'] = 'a' + i;
        for(auto &word: words)
            for(char &ch: word)
                ch = rnk[(int)(ch - 'a')];
        bool chk = 1;
        for(int i = 1; chk && i < n; ++i)
            chk &= words[i - 1] <= words[i];
        return chk;
    }
};
