class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int ans = 0;
        for(auto &word: words)
            ans += word.substr(0, pref.size()) == pref;
        return ans;
    }
};
