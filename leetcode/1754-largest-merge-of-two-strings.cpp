class Solution {
public:
    string largestMerge(string word1, string word2) {
        string ret = "";
        while(!word1.empty() && !word2.empty())
            if(word1 > word2) {
                ret += word1[0];
                word1 = word1.substr(1, word1.length() - 1);
            } else {
                ret += word2[0];
                word2 = word2.substr(1, word2.length() - 1);
            }
        ret += word1 + word2;
        return ret;
    }
};
