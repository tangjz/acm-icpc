class Solution {
public:
    string reversePrefix(string word, char ch) {
        auto p = word.find(ch);
        if(p != string::npos)
            reverse(word.begin(), word.begin() + p + 1);
        return word;
    }
};
