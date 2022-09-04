class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        string ret;
        for(int i = 0, j = 0; i < n || j < m; ) {
            if(i < n)
                ret.push_back(word1[i++]);
            if(j < m)
                ret.push_back(word2[j++]);
        }
        return ret;
    }
};
