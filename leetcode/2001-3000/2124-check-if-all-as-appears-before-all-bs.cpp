class Solution {
public:
    bool checkString(string s) {
        for(int i = 1; i < s.size(); ++i)
            if(s[i - 1] > s[i])
                return 0;
        return 1;
    }
};
