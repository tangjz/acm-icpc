class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char, char> nxt = {
            {'0', '0'},
            {'1', '1'},
            {'6', '9'},
            {'8', '8'},
            {'9', '6'},
        };
        string buf;
        for(char ch: num)
            buf.push_back(nxt[ch]);
        reverse(buf.begin(), buf.end());
        return num == buf;
    }
};
