class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int n = s.size(), c = 0, ans = 0;
        unordered_map<char, int> ctr;
        for(int i = 0, j = 0; i < n; ++i) {
            c += !ctr.count(s[i]);
            ++ctr[s[i]];
            for( ; j < i && c > 2; ++j)
                if(!(--ctr[s[j]])) {
                    --c;
                    ctr.erase(s[j]);
                }
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
