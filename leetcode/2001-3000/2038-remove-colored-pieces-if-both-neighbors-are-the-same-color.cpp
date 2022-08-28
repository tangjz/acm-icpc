class Solution {
public:
    bool winnerOfGame(string s) {
        int n = s.size();
        int ans = 0;
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && s[i] == s[j]; ++j);
            int adt = max(j - i - 2, 0);
            if(s[i] == 'B')
                adt = -adt;
            ans += adt;
        }
        return ans > 0;
    }
};
