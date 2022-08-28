class Solution {
public:
    int minKnightMoves(int tx, int ty) {
        tx = abs(tx);
        ty = abs(ty);
        if(!tx && !ty)
            return 0;
        if(tx < ty)
            swap(tx, ty);
        const int ofs = 3, maxd = 8, dx[maxd] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy[maxd] = {1, -1, 2, -2, 2, -2, 1, -1};
        int maxn = ty + ofs + ofs + 1;
        unordered_map<int, int> dis;
        queue<int> que;
        auto upd = [&](int x, int y, int d) {
            if(x < -ofs || x > tx + ofs || y < -ofs || y > ty + ofs)
                return;
            int msk = (x + ofs) * maxn + (y + ofs);
            auto it = dis.find(msk);
            if(it == dis.end()) {
                // printf("v %d %d %d\n", x, y, d);
                dis.insert({msk, d});
                que.push(msk);
            }
        };
        upd(0, 0, 0);
        while(!que.empty()) {
            int msk = que.front();
            que.pop();
            int ux = (msk / maxn) - ofs, uy = (msk % maxn) - ofs, udis = dis[msk];
            // printf("u %d %d %d\n", ux, uy, udis);
            for(int i = 0; i < maxd; ++i) {
                upd(ux + dx[i], uy + dy[i], udis + 1);
                if(ux + dx[i] == tx && uy + dy[i] == ty)
                    return udis + 1;
            }
        }
        return -1;
    }
};
