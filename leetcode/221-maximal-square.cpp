class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int r = (int)matrix.size();
        if(!r)
            return 0;
        int ans = 0, c = (int)matrix[0].size();
        vector<int> h(c + 1, 0);
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j)
                h[j] = matrix[i][j] == '1' ? h[j] + 1 : 0;
            stack<int> pos;
            for(int j = 0; j <= c; ++j) {
                while(!pos.empty() && h[pos.top()] >= h[j]) {
                    int rht = pos.top();
                    pos.pop();
                    int lft = pos.empty() ? 0 : pos.top() + 1;
                    int len = min(h[rht], j - lft);
                    ans = max(ans, len * len);
                }
                pos.push(j);
            }
        }
        return ans;
    }
};
