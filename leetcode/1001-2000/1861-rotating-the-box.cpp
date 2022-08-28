class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int n = (int)box.size(), m = (int)box[0].size();
        vector<vector<char> > ret(m, vector<char>(n));
        for(int i = 0; i < n; ++i)
            for(int j = m - 1, k = m - 1; j >= 0; --j) {
                for( ; k >= 0 && box[i][k] == '.'; --k);
                if(k < 0 || (box[i][k] == '*' && j != k)) {
                    ret[j][n - 1 - i] = '.';
                } else {
                    ret[j][n - 1 - i] = box[i][k];
                    --k;
                }
            }
        return ret;
    }
};
