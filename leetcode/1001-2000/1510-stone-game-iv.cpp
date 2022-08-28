class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<int> sg(n + 1, 0);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1, k = 1; k <= i; k += (j++) << 1 | 1)
                if(!sg[i - k]) {
                    sg[i] = 1;
                    break;
                }
        }
        return sg[n];
    }
};
