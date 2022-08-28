class Solution {
public:
    int cutOffTree(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), n = r * c;
        map<int, int> pos;
        vector<vector<int> > e(n);
        for(int i = 0, idx = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++idx) {
                if(!mat[i][j])
                    continue;
                if(mat[i][j] > 1)
                    pos[mat[i][j]] = idx;
                if(i > 0 && mat[i - 1][j]) {
                    e[idx - c].push_back(idx);
                    e[idx].push_back(idx - c);
                }
                if(j > 0 && mat[i][j - 1]) {
                    e[idx - 1].push_back(idx);
                    e[idx].push_back(idx - 1);
                }
            }
        vector<int> dis(n);
        queue<int> que;
        auto get_dis = [&](int s, int t) -> int {
            for( ; !que.empty(); que.pop());
            dis.assign(n, -1);
            dis[s] = 0;
            que.push(s);
            while(!que.empty() && dis[t] == -1) {
                int u = que.front();
                que.pop();
                for(int v: e[u])
                    if(dis[v] == -1) {
                        dis[v] = dis[u] + 1;
                        que.push(v);
                    }
            }
            return dis[t];
        };
        int ans = 0, las = 0;
        for(auto &it: pos) {
            if(it.second == las)
                continue;
            int adt = get_dis(las, it.second);
            if(adt == -1)
                return -1;
            ans += adt;
            las = it.second;
        }
        return ans;
    }
};
