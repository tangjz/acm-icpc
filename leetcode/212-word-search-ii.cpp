class Solution {
    struct Node {
        int idx, cnt, msk, nxt;
    };
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        static const int BLEN = 13, BMSK = (1 << BLEN) - 1, maxs = 1 << BLEN | 1;
        static int bits[maxs] = {};
        if(!bits[1])
            for(int i = 1; i < maxs; ++i)
                bits[i] = bits[i >> 1] + (i & 1);
        vector<Node> nodes;
        queue<vector<int> > que;
        sort(words.begin(), words.end());
        nodes.push_back({-1, 0, 0, 0});
        que.push({0, 0, 0, (int)words.size() - 1});
        while(!que.empty()) {
            auto &cur = que.front();
            int rt = cur[0], dep = cur[1], L = cur[2], R = cur[3];
            // printf("cur dep %d L %d R %d\n", dep, L, R);
            que.pop();
            nodes[rt].cnt = R - L + 1;
            nodes[rt].nxt = nodes.size();
            if(words[L].size() == dep)
                nodes[rt].idx = L++;
            for( ; L <= R; ) {
                assert(words[L].size() > dep);
                int o = words[L][dep] - 'a', i = L;
                // puts("ok1");
                for( ; L <= R && words[L][dep] == words[i][dep]; ++L);
                nodes[rt].msk |= 1 << o;
                // printf("nxt %c dep %d L %d R %d\n", words[i][dep], dep + 1, i, L - 1);
                nodes.push_back({-1, 0, 0, 0});
                que.push({(int)nodes.size() - 1, dep + 1, i, L - 1});
                // puts("ok2");
            }
            // puts("ok3");
        }
        int r = board.size(), c = board[0].size();
        vector<int> ids;
        function<void(int, int, Node&)> dfs = [&](int x, int y, Node &rt) {
            char ch = board[x][y];
            board[x][y] = '.';
            if(rt.idx != -1) {
                ids.push_back(rt.idx);
                rt.idx = -1;
                --rt.cnt;
            }
            for(int dx = -1; rt.cnt > 0 && dx <= 1; ++dx)
                for(int dy = -1; rt.cnt > 0 && dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= r || yy < 0 || yy >= c || board[xx][yy] == '.')
                        continue;
                    int o = 1 << (board[xx][yy] - 'a');
                    if(!(rt.msk & o))
                        continue;
                    o = rt.msk & (o - 1);
                    o = rt.nxt + bits[o & BMSK] + bits[o >> BLEN];
                    Node &tr = nodes[o];
                    int pre = tr.cnt;
                    if(pre > 0) {
                        dfs(xx, yy, tr);
                        rt.cnt -= pre - tr.cnt;
                    }
                }
            board[x][y] = ch;
        };
        Node &rt = nodes[0];
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int o = 1 << (board[i][j] - 'a');
                if(!(rt.msk & o))
                    continue;
                o = rt.msk & (o - 1);
                o = rt.nxt + bits[o & BMSK] + bits[o >> BLEN];
                Node &tr = nodes[o];
                int pre = tr.cnt;
                if(pre > 0) {
                    dfs(i, j, tr);
                    rt.cnt -= pre - tr.cnt;
                }
            }
        vector<string> ret;
        for(int x: ids)
            ret.push_back(move(words[x]));
        return ret;
    }
};
