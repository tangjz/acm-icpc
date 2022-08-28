class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        unordered_map<string, int> idx;
        for(auto &it: req_skills)
            idx.insert({it, (int)idx.size()});
        int m = idx.size(), sz = 1 << m;
        vector<int> seq;
        for(auto &it: people) {
            int msk = 0;
            for(auto &jt: it)
                msk |= 1 << idx[jt];
            seq.push_back(msk);
        }
        int n = seq.size();
        static const int maxn = 61, maxs = 1 << 16 | 1;
        static pair<int, int> f[maxn][maxs];
        f[0][0] = {0, 0};
        for(int i = 1; i < sz; ++i)
            f[0][i] = {n + 1, -1};
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < sz; ++j) {
                f[i + 1][j] = {f[i][j].first, j};
            }
            for(int j = 0; j < sz; ++j) {
                int k = j | seq[i];
                f[i + 1][k] = min(f[i + 1][k], make_pair(f[i][j].first + 1, j));
            }
        }
        vector<int> ret;
        for(int i = n, j = sz - 1; i > 0; --i) {
            if(f[i - 1][f[i][j].second].first + 1 == f[i][j].first) {
                ret.push_back(i - 1);
            }
            j = f[i][j].second;
        }
        return ret;
    }
};
