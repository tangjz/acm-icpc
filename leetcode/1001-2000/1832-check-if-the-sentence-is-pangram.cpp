class Solution {
public:
    bool checkIfPangram(string sentence) {
        unordered_set<char> Hash;
        for(char ch: sentence)
            Hash.insert(ch);
        return Hash.size() == 26;
    }
};
