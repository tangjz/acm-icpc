class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        auto chk = [&](string &s) {
            for(int i = 0; i < 2; ++i)
                if(s[i] > s[i + 2])
                    swap(s[i], s[i + 2]);
        };
        chk(s1);
        chk(s2);
        return s1 == s2;
    }
};
