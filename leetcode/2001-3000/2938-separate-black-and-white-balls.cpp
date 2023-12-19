class Solution {
public:
    long long minimumSteps(string s) {
        typedef long long LL;
        int n = s.size();
        LL ans = 0;
        for(int i = 0, j = 0; i < n; ++i)
            if(s[i] == '0')
                ans += i - (j++);
        return ans;
    }
};
