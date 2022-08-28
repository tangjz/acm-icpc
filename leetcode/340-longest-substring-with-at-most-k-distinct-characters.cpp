class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int cnt = 0, ans = 0, n = s.size();
        unordered_map<char, int> ctr;
        for(int i = 0, j = 0; i < n; ++i) {
            if(!ctr.count(s[i])) {
                ++cnt;
                ctr[s[i]] = 1;
            } else {
                ++ctr[s[i]];
            }
            while(cnt > k) {
                if(!(--ctr[s[j]])) {
                    --cnt;
                    ctr.erase(s[j]);
                }
                ++j;
            }
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
