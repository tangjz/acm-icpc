class Solution {
public:
    bool canMakeSubsequence(string A, string B) {
        int n = A.size(), m = B.size(), p = 0;
        for(char ch: A) {
            char nxt = (ch - 'a' + 1) % 26 + 'a';
            p += B[p] == ch || B[p] == nxt;
            if(p == m)
                return 1;
        }
        return 0;
    }
};
