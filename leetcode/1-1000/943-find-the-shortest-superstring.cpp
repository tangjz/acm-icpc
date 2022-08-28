class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        const int INF = 0x3f3f3f3f;
        int n = words.size(), m = 1 << n;
        vector<vector<int> > c(n, vector<int>(n, INF)), f(1 << n, vector<int>(n, INF));
        for(int i = 0; i < n; ++i) {
            f[1 << i][i] = words[i].size();
            for(int j = 0; j < n; ++j) {
                if(i == j)
                    continue;
                int upp = min(words[i].size(), words[j].size());
                for(int com = upp; com >= 0; --com)
                    if(!com || words[i].substr(words[i].size() - com, com) == words[j].substr(0, com)) {
                        c[i][j] = words[j].size() - com;
                        break;
                    }
            }
        }
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                if(f[i][j] == INF)
                    continue;
                for(int k = 0; k < n; ++k) {
                    if((i >> k) & 1)
                        continue;
                    int ii = i | (1 << k);
                    f[ii][k] = min(f[ii][k], f[i][j] + c[j][k]);
                }
            }
        int rem = m - 1, pos = min_element(f[rem].begin(), f[rem].end()) - f[rem].begin();
        vector<int> seq = {pos};
        printf("%d\n", pos);
        for(int i = 1; i < n; ++i) {
            int nxt = rem ^ (1 << pos);
            for(int j = 0; j < n; ++j)
                if(f[nxt][j] + c[j][pos] == f[rem][pos]) {
                    pos = j;
                    break;
                }
            rem = nxt;
            seq.push_back(pos);
            printf("%d\n", pos);
        }
        int las = seq.back();
        string ret = words[las];
        seq.pop_back();
        printf("%d %s\n", las, ret.c_str());
        while(!seq.empty()) {
            int com = words[seq.back()].size() - c[las][seq.back()];
            las = seq.back();
            ret += words[las].substr(com);
            seq.pop_back();
            printf("%d %s\n", las, ret.c_str());
        }
        return ret;
    }
};
