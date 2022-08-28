class Solution {
    bool check(int n, vector<int>& A, int m, vector<int>& B, int q, int dt) {
        int cnt = 0, bound = 0, used = 0;
        deque<int> que;
        // printf("check %d\n", n);
        for(int i = n - 1, j = m - 1; i >= 0; --i) {
            // printf("match %d\n", A[i]);
            while(j >= 0 && A[i] <= B[j] + dt) {
                que.push_back(B[j--]);
            }
            ++bound;
            while(!que.empty() && A[i] <= que.front()) {
                // printf("use %d\n", que.front());
                que.pop_front();
                ++cnt;
            }
            while(cnt < bound) {
                if(que.empty() || used >= q) {
                    return false;
                }
                // printf("use %d + %d\n", que.back(), dt);
                que.pop_back();
                ++cnt;
                ++used;
            }
        }
        return true;
    }
public:
    int maxTaskAssign(vector<int>& A, vector<int>& B, int adt, int dlt) {
        int n = A.size(), m = B.size();
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        int L = 0, R = min(n, m);
        while(L < R) {
            int M = (L + R + 1) >> 1;
            if(check(M, A, m, B, adt, dlt)) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        // puts("");
        return L;
    }
};
