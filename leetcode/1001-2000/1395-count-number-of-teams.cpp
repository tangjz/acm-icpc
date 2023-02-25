class Solution {
public:
    int numTeams(vector<int>& a) {
        int n = (int)a.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            int c00 = 0, c01 = 0, c10 = 0, c11 = 0;
            for(int j = 0; j < i; ++j)
                a[j] < a[i] ? (++c00) : (++c01);
            for(int j = i + 1; j < n; ++j)
                a[j] < a[i] ? (++c10) : (++c11);
            ans += c00 * c11 + c01 * c10;
        }
        return ans;
    }
};
