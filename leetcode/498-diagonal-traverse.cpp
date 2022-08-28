class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<int> ord(n * m);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            int ux = u / m, uy = u % m;
            int vx = v / m, vy = v % m;
            int dt = (ux + uy) - (vx + vy);
            return dt ? dt < 0 : ((ux + uy) & 1 ? ux < vx : uy < vy);
        });
        for(int &u: ord) {
            int ux = u / m, uy = u % m;
            u = mat[ux][uy];
        }
        return ord;
    }
};
