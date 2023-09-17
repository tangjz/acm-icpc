class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size(), ans = 0;
        unordered_set<char> sp;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && !sp.count(s[j]); ++j)
                sp.insert(s[j]);
            ans = max(ans, j - i);
            sp.erase(s[i]);
        }
        return ans;
    }
};
