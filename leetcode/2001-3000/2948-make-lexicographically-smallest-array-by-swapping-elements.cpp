class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& A, int dt) {
        int n = A.size();
        vector<int> ord(n), que;
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return A[u] < A[v];
        });
        que.reserve(n);
        for(int i = 0, j; i < n; i = j) {
            que.clear();
            que.push_back(A[ord[i]]);
            for(j = i + 1; j < n && A[ord[j]] - A[ord[j - 1]] <= dt; ++j)
                que.push_back(A[ord[j]]);
            if(que.size() == 1)
                continue;
            sort(ord.begin() + i, ord.begin() + j);
            for(int u = i, v = 0; u < j; ++u, ++v)
                A[ord[u]] = que[v];
        }
        return A;
    }
};
