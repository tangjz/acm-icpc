class Solution {
public:
    char repeatedCharacter(string s) {
        unordered_set<char> vis;
        for(char ch: s) {
            if(!vis.insert(ch).second)
                return ch;
        }
        return '\0';
    }
};
