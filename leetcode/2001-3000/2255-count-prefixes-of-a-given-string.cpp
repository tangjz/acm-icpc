class Solution {
public:
    int countPrefixes(vector<string>& words, string s) {
        int ans = 0;
        for(auto &word: words)
            ans += s.substr(0, word.size()) == word;
        return ans;
    }
};
