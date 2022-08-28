class Solution {
public:
    int trafficCommand(vector<string>& directions) {
        const char *pat = "ESWN";
        vector<int> sz(4);
        vector<vector<int> > dt(4);
        for(int i = 0; i < 4; ++i) {
            sz[i] = directions[i].size();
            for(int j = 0; j < sz[i]; ++j)
                for(int k = 0; k < 4; ++k)
                    if(pat[k] == directions[i][j]) {
                        dt[i].push_back(k);
                        break;
                    }
        }
        static int dp[21][21][21][21];
        dp[0][0][0][0] = 0;
        vector<int> u(4), v(4), ofs(4);
        for(u[0] = 0; u[0] <= sz[0]; ++u[0])
            for(u[1] = 0; u[1] <= sz[1]; ++u[1])
                for(u[2] = 0; u[2] <= sz[2]; ++u[2])
                    for(u[3] = 0; u[3] <= sz[3]; ++u[3]) {
                        if(!u[0] && !u[1] && !u[2] && !u[3])
                            continue;
                        int &cur = dp[u[0]][u[1]][u[2]][u[3]] = INT_MAX;
                        for(int msk = 1; msk < 16; ++msk) {
                            bool ban = 0;
                            for(int i = 0; i < 4; ++i) {
                                v[i] = u[i] - ((msk >> i) & 1);
                                if(v[i] < 0) {
                                    ban = 1;
                                    break;
                                }
                                ofs[i] = v[i] < u[i] ? (dt[i][v[i]] - i + 4) & 3 : 0;
                            }
                            for(int i = 0; !ban && i < 4; ++i) {
                                switch(ofs[i]) {
                                    case 0: case 3: {
                                        break;
                                    }
                                    case 1: {
                                        int j = (i + 1) & 3;
                                        ban |= v[j] < u[j] && ofs[j] != 3;
                                        j = (j + 1) & 3;
                                        ban |= v[j] < u[j] && ofs[j] != 1;
                                        j = (j + 1) & 3;
                                        ban |= v[j] < u[j] && ofs[j] != 3;
                                        break;
                                    }
                                    case 2: {
                                        int j = (i + 1) & 3;
                                        ban |= v[j] < u[j] && ofs[j] != 3;
                                        j = (j + 1) & 3;
                                        ban |= v[j] < u[j] && ofs[j] == 1;
                                        j = (j + 1) & 3;
                                        ban |= v[j] < u[j];
                                        break;
                                    }
                                }
                            }
                            if(ban)
                                continue;
                            int &pre = dp[v[0]][v[1]][v[2]][v[3]];
                            if(pre < INT_MAX)
                                cur = min(cur, pre + 1);
                        }
                    }
        return dp[sz[0]][sz[1]][sz[2]][sz[3]];
    }
};
