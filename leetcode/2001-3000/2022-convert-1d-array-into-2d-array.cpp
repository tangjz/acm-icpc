class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& seq, int m, int n) {
        if(seq.size() != m * n)
            return {};
        vector<vector<int> > ret;
        for(int i = 0; i < m; ++i)
            ret.push_back(vector<int>(seq.begin() + i * n, seq.begin() + (i + 1) * n));
        return ret;
    }
};
