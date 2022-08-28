class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        long long ans0 = 0, ans1 = 0;
        int cnt0 = 0;
        for(char ch: text) {
            if(ch == pattern[1]) {
                ans0 += cnt0 + 1;
                ans1 += cnt0;
            }
            cnt0 += ch == pattern[0];
        }
        ans1 += cnt0;
        return max(ans0, ans1);
    }
};
