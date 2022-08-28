class Solution {
public:
    bool divisorGame(int n) {
        vector<bool> sg(n + 1);
        for(int i = 2; i <= n; ++i)
            for(int j = 1; j * j <= i; ++j) {
                if(i % j > 0)
                    continue;
                if(!sg[i - j] || (j > 1 && !sg[i - i / j])) {
                    sg[i] = 1;
                    break;
                }
            }
        return sg[n];
    }
};
