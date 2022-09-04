class Solution {
public:
    string firstPalindrome(vector<string>& words) {
        for(auto &word: words) {
            string rev = word;
            reverse(rev.begin(), rev.end());
            if(word == rev)
                return word;
        }
        return "";
    }
};
