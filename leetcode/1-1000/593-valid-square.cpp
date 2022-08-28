class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int> > p = {p1, p2, p3, p4}, dt(4, vector<int>(2));
        sort(p.begin() + 1, p.end());
        do {
            for(int i = 0, j = 1; i < 4; ++i, (++j) == 4 && (j = 0)) {
                dt[i][0] = p[j][0] - p[i][0];
                dt[i][1] = p[j][1] - p[i][1];
            }
            int len = dt[0][0] * dt[0][0] + dt[0][1] * dt[0][1];
            bool ban = !len;
            for(int i = 0, j = 1; !ban && i < 4; ++i, (++j) == 4 && (j = 0)) {
                int tmp = dt[i][0] * dt[i][0] + dt[i][1] * dt[i][1];
                if(len != tmp) {
                    ban = 1;
                    break;
                }
                tmp = dt[i][0] * dt[j][0] + dt[i][1] * dt[j][1];
                if(tmp)
                    ban = 1;
            }
            if(!ban)
                return 1;
        } while(next_permutation(p.begin() + 1, p.end()));
        return 0;
    }
};
