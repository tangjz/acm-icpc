class Solution {
public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        vector<string> ret;
        for(int i = 0; i < n; ) {
            ret.push_back(words[i]);
            for(int u = groups[i]; i < n && groups[i] == u; ++i);
        }
        return ret;
    }
};
