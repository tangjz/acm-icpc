class Solution {
    const static int maxn = 6, row = 2, col = 3;
    struct Permutation {
        int nxt[maxn];
        bool operator < (Permutation const &t) const {
            for(int i = 0; i < maxn; ++i)
                if(nxt[i] != t.nxt[i])
                    return nxt[i] < t.nxt[i];
            return 0;
        }
        bool operator == (Permutation const &t) const {
            for(int i = 0; i < maxn; ++i)
                if(nxt[i] != t.nxt[i])
                    return 0;
            return 1;
        }
    } ;
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        map<Permutation, int> dis;
        vector<Permutation> que;
        Permutation cur, pat;
        for(int i = 0, idx = 0; i < row; ++i)
            for(int j = 0; j < col; ++j, ++idx) {
                cur.nxt[idx] = board[i][j];
                pat.nxt[idx] = idx + 1;
            }
        pat.nxt[maxn - 1] = 0;
        que.push_back(cur);
        dis[cur] = 0;
        for(int i = 0; i < (int)que.size(); ++i) {
            cur = que[i];
            if(cur == pat)
                return dis[cur];
            int idx, dist = dis[cur] + 1;
            for(int i = 0; i < maxn; ++i)
                if(!cur.nxt[i]) {
                    idx = i;
                    break;
                }
            int x = idx / col, y = idx % col;
            if(x) {
                swap(cur.nxt[idx], cur.nxt[idx - col]);
                if(dis.find(cur) == dis.end()) {
                    que.push_back(cur);
                    dis[cur] = dist;
                }
                swap(cur.nxt[idx], cur.nxt[idx - col]);
            } else {
                swap(cur.nxt[idx], cur.nxt[idx + col]);
                if(dis.find(cur) == dis.end()) {
                    que.push_back(cur);
                    dis[cur] = dist;
                }
                swap(cur.nxt[idx], cur.nxt[idx + col]);
            }
            if(y) {
                swap(cur.nxt[idx], cur.nxt[idx - 1]);
                if(dis.find(cur) == dis.end()) {
                    que.push_back(cur);
                    dis[cur] = dist;
                }
                swap(cur.nxt[idx], cur.nxt[idx - 1]);
            }
            if(y + 1 < col) {
                swap(cur.nxt[idx], cur.nxt[idx + 1]);
                if(dis.find(cur) == dis.end()) {
                    que.push_back(cur);
                    dis[cur] = dist;
                }
                swap(cur.nxt[idx], cur.nxt[idx + 1]);
            }
        }
        return -1;
    }
};
