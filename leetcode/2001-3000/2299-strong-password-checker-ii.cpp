class Solution {
public:
    bool strongPasswordCheckerII(string pswd) {
        if(pswd.size() < 8)
            return 0;
        static string pat = "!@#$%^&*()-+";
        static unordered_set<char> sp(pat.begin(), pat.end());
        int msk = 0;
        char las = '\0';
        for(char ch: pswd) {
            if(ch == las)
                return 0;
            las = ch;
            msk |= !!isdigit(ch) << 0;
            if(isalpha(ch)) {
                msk |= !!islower(ch) << 1;
                msk |= !!isupper(ch) << 2;
            }
            msk |= !!sp.count(ch) << 3;
        }
        return msk == 15;
    }
};
