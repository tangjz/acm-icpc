class Solution {
public:
    long long sumScores(string s) {
        int n = s.size();
        long long ans = n;
        vector<int> z(n);
        z[0] = n;
        for(int i = 1, j = 1, k; i < n; i = k) {
            j = max(j, i);
            for( ; j < n && s[j] == s[j - i]; ++j);
            ans += z[i] = j - i;
            for(k = i + 1; k + z[k - i] < j; ans += z[k] = z[k - i], ++k);
        }
        return ans;
    }
};
