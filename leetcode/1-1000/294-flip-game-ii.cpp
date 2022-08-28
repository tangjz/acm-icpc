class Solution {
public:
    bool canWin(string A) {
        static const int low = 53, per = 34, sg[87] = {0, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 0, 5, 2, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 2, 7, 4, 0, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9};
        int n = A.size();
        // vector<int> sg(n + 1), tim(n + 1);
        // for(int i = 2; i <= n; ++i) {
        //     for(int j = 0; j + 2 <= i; ++j) {
        //         int nxt = sg[j] ^ sg[i - 2 - j];
        //         if(nxt <= n)
        //             tim[nxt] = i;
        //     }
        //     for( ; tim[sg[i]] == i; ++sg[i]);
        // }
        int ret = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && A[i] == A[j]; ++i);
            if(A[j] == '+') {
                int k = i - j;
                ret ^= sg[k < low ? k : (k - low) % per + low];
            }
        }
        return ret;
    }
};
