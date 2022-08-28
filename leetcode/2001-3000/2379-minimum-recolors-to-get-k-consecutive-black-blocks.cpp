class Solution {
public:
    int minimumRecolors(string a, int k) {
        int n = a.size(), ans = k;
        for(int i = 0; i <= n - k; ++i) {
            int tmp = 0;
            for(int j = 0; j < k; ++j)
                tmp += a[i + j] == 'W';
            ans = min(ans, tmp);
        }
        return ans;
    }
};
