class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        vector<vector<int> > ret;
        for(int &x: rowSum) {
            vector<int> row;
            for(int &y: colSum) {
                int d = min(x, y);
                row.push_back(d);
                x -= d;
                y -= d;
            }
            ret.push_back(row);
        }
        return ret;
    }
};
