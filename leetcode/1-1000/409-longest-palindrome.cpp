class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> ctr;
        for(char ch : s)
            ++ctr[ch];
        bool hasOdd = 0;
        int ret = 0;
        for(auto &it : ctr)
            if(it.second & 1) {
                hasOdd = 1;
                ret += it.second - 1;
            } else {
                ret += it.second;
            }
        ret += hasOdd;
        return ret;
    }
};
