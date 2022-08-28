class Solution {
public:
    int minDistance(vector<int>& a, int k) {
        sort(a.begin(), a.end());
        int n = a.size();
        vector<vector<int> > cost(n, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j) {
                int sz = j - i + 1;
                vector<int> vec(a.begin() + i, a.begin() + j + 1);
                nth_element(vec.begin(), vec.begin() + ((sz - 1) >> 1), vec.end());
                int mid = vec[(sz - 1) >> 1], &sum = cost[i][j];
                for(int x : vec)
                    sum += abs(x - mid);
            }
        vector<int> f(n + 1, INT_MAX);
        f[0] = 0;
        for(int i = 0; i < k; ++i) {
            vector<int> g(n + 1, INT_MAX);
            for(int L = 0; L < n; ++L) if(f[L] < INT_MAX)
                for(int R = L; R < n; ++R)
                    g[R + 1] = min(g[R + 1], f[L] + cost[L][R]);
            f = move(g);
        }
        return f[n];
    }
};
