class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vis = {'a', 'e', 'i', 'o', 'u'};
        int ans = 0, sum = 0, pos = 0;
        for(char ch : s) {
            sum += vis.count(ch);
            if(pos >= k) {
                sum -= vis.count(s[pos - k]);
            }
            if(pos >= k - 1) {
                ans = max(ans, sum);
            }
            ++pos;
        }
        return ans;
    }
};
