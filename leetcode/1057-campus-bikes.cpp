class Solution {
public:
    vector<int> assignBikes(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size(), m = B.size();
        vector<pair<int, pair<int, int> > > ord;
        ord.reserve(n * m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int dis = abs(A[i][0] - B[j][0]) + abs(A[i][1] - B[j][1]);
                ord.push_back({dis, {i, j}});
            }
        sort(ord.begin(), ord.end());
        vector<int> ret(n, -1);
        vector<bool> vis(m);
        for(auto &it: ord) {
            int i, j;
            tie(i, j) = it.second;
            if(ret[i] == -1 && !vis[j]) {
                ret[i] = j;
                vis[j] = 1;
            }
        }
        return ret;
    }
};
