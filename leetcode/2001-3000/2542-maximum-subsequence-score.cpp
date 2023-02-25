class Solution {
public:
    long long maxScore(vector<int>& A, vector<int>& B, int k) {
        typedef long long LL;
        int n = A.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return B[u] > B[v];
        });
        LL ans = 0, sum = 0;
        priority_queue<int> que;
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            sum += A[u];
            que.push(-A[u]);
            if(i >= k - 1) {
                ans = max(ans, B[u] * sum);
                sum += que.top();
                que.pop();
            }
        }
        return ans;
    }
};
