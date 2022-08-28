class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> ctr;
        for(char ch: s)
            ++ctr[ch];
        int odd = 0;
        for(auto &it: ctr)
            if(it.second & 1 && (++odd) > 1)
                return 0;
        return 1;
    }
};
