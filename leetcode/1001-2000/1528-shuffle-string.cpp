class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string t = s;
        int pos = 0;
        for(int nxt : indices) {
            t[nxt] = s[pos++];
        }
        return t;
    }
};
