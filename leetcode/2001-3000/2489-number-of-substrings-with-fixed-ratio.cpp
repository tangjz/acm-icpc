class Solution {
public:
    long long fixedRatio(string s, int num1, int num2) {
        typedef long long LL;
        unordered_map<LL, int> Hash;
        LL ans = 0, cur = 0;
        ++Hash[0];
        for(char ch: s) {
            cur += ch == '0' ? -num2 : num1;
            ans += Hash[cur]++;
        }
        return ans;
    }
};
