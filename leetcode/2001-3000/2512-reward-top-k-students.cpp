class Solution {
public:
    vector<int> topStudents(vector<string>& pf, vector<string>& nf, vector<string>& rp, vector<int>& sid, int k) {
        int n = sid.size();
        vector<pair<int, int> > score(n);
        vector<int> ord(n);
        unordered_map<string, int> Hash;
        for(auto &it: pf)
            Hash.insert({it, 3});
        for(auto &it: nf)
            Hash.insert({it, -1});
        for(int i = 0; i < n; ++i) {
            auto &it = rp[i];
            int m = it.size();
            for(int j = 0, k; j < m; ) {
                if(it[j] == ' ') {
                    ++j;
                    continue;
                }
                for(k = j; j < m && it[j] != ' '; ++j);
                auto jt = Hash.find(it.substr(k, j - k));
                if(jt != Hash.end())
                    score[i].first += jt -> second;
            }
            score[i].second = -sid[i];
            ord[i] = i;
        }
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return score[u] > score[v];
        });
        ord.resize(k);
        for(auto &it: ord)
            it = sid[it];
        return ord;
    }
};
