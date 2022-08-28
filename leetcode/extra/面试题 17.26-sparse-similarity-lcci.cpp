class Solution {
public:
    vector<string> computeSimilarities(vector<vector<int>>& docs) {
        int n = docs.size();
        vector<vector<int> > ctr(n, vector<int>(n));
        unordered_map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            for(int x: docs[i])
                pos[x].push_back(i);
        for(auto &it: pos) {
            auto &vec = it.second;
            for(int x: vec)
                for(int y: vec)
                    ++ctr[x][y];
        }
        vector<string> ret;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                if(!ctr[i][j])
                    continue;
                static char buf[17];
                sprintf(buf, "%d,%d: %.4f", i, j, (double)ctr[i][j] / (docs[i].size() + docs[j].size() - ctr[i][j]) + 1e-9);
                ret.push_back((string)buf);
            }
        return ret;
    }
};
