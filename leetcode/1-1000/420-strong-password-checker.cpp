class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.size(), ctr[3] = {}, m = 0;
        bool vis[3] = {};
        for(int i = 0, j; i < n; ) {
            char ch = password[i];
            vis[0] |= isdigit(ch);
            vis[1] |= islower(ch);
            vis[2] |= isupper(ch);
            for(j = i; i < n && ch == password[i]; ++i);
            j = i - j;
            if(j >= 3)
                ++ctr[j % 3];
            m += j / 3;
        }
        int p = !vis[0] + !vis[1] + !vis[2];
        if(n < 6)
            return max(max(m, p), 6 - n);
        if(n <= 20)
            return max(m, p);
        for(int i = 0, q = n - 20; i < 3; ++i) {
            int t = min(q / (i + 1), i + 1 < 3 ? ctr[i] : INT_MAX);
            q -= t * (i + 1);
            m -= t;
        }
        return n - 20 + max(m, p);
    }
};
