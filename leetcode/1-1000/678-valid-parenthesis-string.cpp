class Solution {
public:
    bool checkValidString(string s) {
        int L = 0, R = 0;
        for(char ch : s) {
            L = ch == '(' ? L + 1 : max(L - 1, 0);
            R = ch == ')' ? R - 1 : R + 1;
            if(R < 0)
                return 0;
        }
        return L == 0;
    }
};
