class Solution {
public:
    string decodeMessage(string key, string message) {
        static const int maxd = 26;
        char cur = 'a', nxt[maxd + 1] = {};
        for(char ch: key) {
            if(ch == ' ')
                continue;
            int o = ch - 'a';
            if(!nxt[o])
                nxt[o] = cur++;
        }
        for(char &ch: message)
            if(ch != ' ')
                ch = nxt[(int)(ch - 'a')];
        return message;
    }
};
