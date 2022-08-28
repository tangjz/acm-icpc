class Solution {
public:
    string freqAlphabets(string s) {
        int len = (int)s.size();
        string t = "";
        for(int i = len - 1; i >= 0; ) {
            int val;
            if(s[i] == '#') {
                val = (s[i - 2] - '0');
                val = val * 10 + (s[i - 1] - '0');
                i -= 3;
            } else {
                val = (s[i] - '0');
                i -= 1;
            }
            t.push_back('a' + (val - 1));
        }
        reverse(t.begin(), t.end());
        return t;
    }
};
