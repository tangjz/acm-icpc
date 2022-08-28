class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();
        vector<int> seq(n);
        for(int i = 0; i < n; ++i)
            seq[i] = (dist[i] - 1) / speed[i] + 1;
        sort(seq.begin(), seq.end());
        int m = 0;
        for( ; m < n && seq[m] > m; ++m);
        return m;
    }
};
