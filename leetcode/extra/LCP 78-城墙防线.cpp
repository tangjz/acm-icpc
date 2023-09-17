class Solution {
public:
    int rampartDefensiveLine(vector<vector<int>>& rampart) {
        int n = rampart.size();
        vector<int> rem(n);
        for(int i = 1; i < n; ++i) {
            rem[i] = rampart[i][0] - rampart[i - 1][1];
            rem[0] += rem[i];
        }
        int L = 0, R = rem[0] / (n - 2);
        while(L < R) {
            int M = (L + R + 1) >> 1, cur = 0;
            bool bad = 0;
            for(int i = 1; i < n; ++i) {
                if(cur > rem[i]) {
                    bad = 1;
                    break;
                }
                cur = max(M - rem[i] + cur, 0);
            }
            if(bad) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
