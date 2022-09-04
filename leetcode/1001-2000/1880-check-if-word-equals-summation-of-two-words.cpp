class Solution {
public:
    bool isSumEqual(string A, string B, string C) {
        auto toInt = [&](string &s) {
            for(char &ch: s)
                ch = ch - 'a' + '0';
            return stoi(s);
        };
        return toInt(A) + toInt(B) == toInt(C);
    }
};
