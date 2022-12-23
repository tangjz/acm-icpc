class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = s.size(), c[3] = {};
        for(int i = 0; i < n; ++i)
            ++c[s[i] -= 'a'];
        for(int i = 0; i < 3; ++i)
            if(c[i] < k)
                return -1;
        int ans = n;
        for(int i = 0, j = 0; i < n; ++i) {
            if(i > j)
                --c[s[j++]];
            for( ; j < n && c[s[j]] > k; --c[s[j++]]);
            ans = min(ans, i + n - j);
            ++c[s[i]];
        }
        return ans;
    }
};
