class Solution {
public:
    string minWindow(string s, string t) {
        int n = (int)s.length();
        unordered_map<char, int> ctr, upp;
        for(char ch : t)
            ++upp[ch];
        int rem = (int)upp.size(), len = n + 1, pos = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && rem > 0; ++j) {
                char ch = s[j];
                rem -= ctr[ch] == upp[ch] - 1;
                ++ctr[ch];
            }
            if(!rem && len > j - i) {
                len = j - i;
                pos = i;
            }
            char ch = s[i];
            auto it = upp.find(ch);
            rem += it != upp.end() && ctr[ch] == upp[ch];
            --ctr[ch];
        }
        return len <= n ? s.substr(pos, len) : "";
    }
};
