class Solution {
public:
    vector<int> circularGameLosers(int n, int k) {
        int p = 0;
        vector<bool> vis(n);
        for(int i = k % n, j = 0; !vis[p]; ) {
            vis[p] = 1;
            (j += i) >= n && (j -= n);
            (p += j) >= n && (p -= n);
        }
        vector<int> seq;
        for(int i = 0; i < n; ++i)
            if(!vis[i])
                seq.push_back(i + 1);
        return seq;
    }
};
