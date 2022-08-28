class Solution {
    static const int maxc = 26, maxs = 1 << 7 | 1;
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int n = words.size(), m = puzzles.size(), upp = 0;
        vector<int> msk(m);
        vector<vector<pair<int, int> > > ctr(maxc);
        for(int i = 0; i < m; ++i) {
            int &s = msk[i] = 0, c = 0;
            for(char ch: puzzles[i]) {
                int o = ch - 'a';
                if(!((s >> o) & 1)) {
                    ++c;
                    s |= 1 << o;
                }
            }
            upp = max(upp, c);
            ctr[puzzles[i].front() - 'a'].push_back({s, 0});
        }
        for(int i = 0; i < maxc; ++i) {
            sort(ctr[i].begin(), ctr[i].end());
            ctr[i].erase(unique(ctr[i].begin(), ctr[i].end()), ctr[i].end());
        }
        for(auto &it: words) {
            int s = 0;
            vector<int> cand;
            for(char ch: it) {
                int o = ch - 'a';
                if(!((s >> o) & 1)) {
                    cand.push_back(o);
                    s |= 1 << o;
                }
            }
            if(cand.size() > upp)
                continue;
            for(int i: cand)
                for(auto &jt: ctr[i])
                    if((jt.first & s) == s)
                        ++jt.second;
        }
        vector<int> ret(m);
        for(int i = 0; i < m; ++i)
            for(auto &it: ctr[puzzles[i].front() - 'a'])
                if(it.first == msk[i]) {
                    ret[i] = it.second;
                    break;
                }
        return ret;
    }
};
