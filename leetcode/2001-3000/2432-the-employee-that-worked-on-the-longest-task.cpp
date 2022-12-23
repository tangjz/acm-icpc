class Solution {
public:
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int m = logs.size();
        vector<int> ctr(n);
        for(int i = 0; i < m; ++i) {
            int pos = logs[i][0], las = i ? logs[i - 1][1] : 0, cur = logs[i][1];
            ctr[pos] = max(ctr[pos], cur - las);
        }
        m = 0;
        for(int i = 1; i < n; ++i)
            if(ctr[i] > ctr[m])
                m = i;
        return m;
    }
};
