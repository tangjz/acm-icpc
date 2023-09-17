class Solution {
public:
    int minimizeMax(vector<int>& A, int p) {
        const int INF = 0x3f3f3f3f;
        int n = A.size();
        sort(A.begin(), A.end());
        int L = 0, R = A[n - 1] - A[0];
        while(L < R) {
            int M = (L + R) >> 1, f[2][2] = {}, cur = 0, pre = 1;
            f[0][0] = 0;
            f[0][1] = -INF;
            // printf("M %d\n", M);
            for(int i = 1; i < n; ++i) {
                swap(cur, pre);
                f[cur][0] = max(f[pre][0], f[pre][1]);
                if(A[i] - A[i - 1] > M || f[pre][0] == -INF) {
                    f[cur][1] = -INF;
                } else {
                    f[cur][1] = f[pre][0] + 1;
                }
                // printf("i %d %d: %d %d\n", i, A[i], f[cur][0], f[cur][1]);
            }
            if(max(f[cur][0], f[cur][1]) < p) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
