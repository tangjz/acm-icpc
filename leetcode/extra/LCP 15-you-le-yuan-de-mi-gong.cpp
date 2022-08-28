class Solution {
public:
    vector<int> visitOrder(vector<vector<int>>& points, string direction) {
        int n = points.size();
        vector<bool> vis(n);
        vector<int> ret = {0};
        for(int i = 1; i < n; ++i)
            if(points[i] < points[ret.back()])
                ret.back() = i;
        vis[ret.back()] = 1;
        auto det = [&](vector<int> &A, vector<int> &B, vector<int> &C) {
            int xB = B[0] - A[0], yB = B[1] - A[1];
            int xC = C[0] - A[0], yC = C[1] - A[1];
            return xB * yC - xC * yB;
        };
        for(int i = 0; i < n - 2; ++i) {
            ret.push_back(-1);
            for(int j = 0; j < n; ++j) {
                if(vis[j])
                    continue;
                if(ret.back() == -1) {
                    ret.back() = j;
                    continue;
                }
                int val = det(points[ret[i]], points[ret.back()], points[j]);
                if((direction[i] == 'L') == (val < 0))
                    ret.back() = j;
            }
            vis[ret.back()] = 1;
        }
        for(int i = 0; i < n; ++i)
            if(!vis[i]) {
                ret.push_back(i);
                break;
            }
        return ret;
    }
};
