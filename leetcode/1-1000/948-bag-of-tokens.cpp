class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size(), ans = 0;
        sort(tokens.begin(), tokens.end());
        for(int i = 0, j = 0, c = power, d = power; i < n - i; ++i) {
            // power - [0, j) + [n - i, n) < 0
            if(i > 0) {
                d -= tokens[i - 1];
                if(d < 0)
                    break;
                d += tokens[n - i];
                if(j > n - i) {
                    c += tokens[--j];
                } else if(j < i) {
                    c -= tokens[j++];
                }
                c += tokens[n - i];
            }
            for( ; j < n - i && c - tokens[j] >= 0; c -= tokens[j++]);
            ans = max(ans, j - i);
        }
        return ans;
    }
};
