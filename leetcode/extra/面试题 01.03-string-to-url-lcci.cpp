class Solution {
public:
    string replaceSpaces(string S, int length) {
        int m = length;
        for(int i = 0; i < length; ++i)
            if(S[i] == ' ')
                m += 2;
        S.resize(m);
        for(int i = length - 1; i >= 0; --i)
            if(S[i] == ' ') {
                S[--m] = '0';
                S[--m] = '2';
                S[--m] = '%';
            } else {
                S[--m] = S[i];
            }
        return move(S);
    }
};
