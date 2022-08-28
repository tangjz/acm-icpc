class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        vector<int> row(n), col(m);
        for(auto &it : indices) {
            row[it[0]] ^= 1;
            col[it[1]] ^= 1;
        }
        int cntR = 0, cntC = 0;
        for(int x : row)
            cntR += x;
        for(int x : col)
            cntC += x;
        return cntR * (m - cntC) + (n - cntR) * cntC;
    }
};
