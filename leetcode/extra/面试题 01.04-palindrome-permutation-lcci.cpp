class Solution {
public:
    bool canPermutePalindrome(string s) {
		unordered_map<char, int> ctr;
        for(char ch: s)
			++ctr[ch];
		int cnt = 0;
        for(auto &it: ctr)
            cnt += it.second & 1;
        return cnt < 2;
    }
};
