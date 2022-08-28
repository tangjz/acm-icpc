class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        int n = s.size(), m = 0, ans = 0;
        unordered_map<char, int> ctr;
        for(int i = 0; i < n; ++i) {
            m += !(ctr[s[i]]++);
            if(i >= k - 1) {
                ans += m == k;
                m -= !(--ctr[s[i - (k - 1)]]);
            }
        }
        return ans;
    }
};
