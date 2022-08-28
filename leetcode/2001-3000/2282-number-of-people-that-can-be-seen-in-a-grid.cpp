class Solution {
public:
    vector<vector<int>> seePeople(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        vector<stack<int> > row(r), col(c);
        for(int i = r - 1; i >= 0; --i)
            for(int j = c - 1; j >= 0; --j) {
                int val = mat[i][j];
                int &cnt = mat[i][j] = 0;
                for(int las = -1, cur; !row[i].empty() && (cur = row[i].top()) < val; row[i].pop(), cnt += las < cur, las = cur);
                cnt += !row[i].empty();
                row[i].push(val);
                for(int las = -1, cur; !col[j].empty() && (cur = col[j].top()) < val; col[j].pop(), cnt += las < cur, las = cur);
                cnt += !col[j].empty();
                col[j].push(val);
            }
        return mat;
    }
};
