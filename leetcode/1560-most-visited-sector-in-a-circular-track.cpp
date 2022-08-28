class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        int m = (int)rounds.size() - 1;
        vector<int> ctr(n);
        for(int i = 0; i < m; ++i)
            for(int j = rounds[i] - 1, k = rounds[i + 1] - 1; j != k; j = (j + 1) % n)
                ++ctr[j];
        ++ctr[rounds[m] - 1];
        int ans = -1;
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            int cur = ctr[i];
            if(ans < cur) {
                ans = cur;
                vector<int>().swap(ret);
            }
            if(ans == cur)
                ret.push_back(i + 1);
        }
        return ret;
    }
};
