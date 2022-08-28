class Solution {
public:
    string gobang(vector<vector<int>>& pieces) {
        const int maxd = 4, dx[] = {0, 1, 1, 1}, dy[] = {1, -1, 0, 1};
        set<vector<int> > vis;
        map<vector<int>, vector<int> > ctr;
        for(auto &it: pieces) {
            int x = it[0], y = it[1], t = it[2];
            vis.insert({x, y, t});
            // printf("insert %d %d %d\n", x, y, t);
            for(int d = 0; d < maxd; ++d)
                for(int ofs = -4; ofs <= 0; ++ofs) {
                    int px = x + dx[d] * ofs, py = y + dy[d] * ofs;
                    auto it = ctr.insert({{px, py, d}, {0, 0}}).first;
                    ++(it -> second)[t];
                    // if(px == 3 && py == 2 && d == 2)
                    //     printf("%d %d %d: %d %d\n", px, py, d, (it -> second)[0], (it -> second)[1]);
                }
        }
        // step 1
        for(auto &it: ctr)
            if(it.second[0] == 4 && !it.second[1])
                return "Black";
        // step 2
        set<vector<int> > cand1;
        for(auto &it: ctr)
            if(it.second[1] == 4 && !it.second[0]) {
                int x = it.first[0], y = it.first[1], d = it.first[2];
                // printf("white check %d %d %d\n", x, y, d);
                for(int i = 0; i < 5; ++i, x += dx[d], y += dy[d])
                    if(!vis.count({x, y, 1})) {
                        // printf("white cand %d %d\n", x, y);
                        cand1.insert({x, y});
                        break;
                    }
                if(cand1.size() > 1)
                    break;
            }
        if(cand1.size() > 1)
            return "White";
        // step 3
        set<vector<int> > cand0;
        // printf("cand1 sz %d\n", (int)cand1.size());
        if(cand1.empty()) { // choose 3 black
            for(auto &it: ctr)
                if(it.second[0] == 3 && !it.second[1]) {
                    int x = it.first[0], y = it.first[1], d = it.first[2];
                    for(int i = 0; i < 5; ++i, x += dx[d], y += dy[d])
                        if(!vis.count({x, y, 0})) {
                            cand1.insert({x, y});
                            break;
                        }
                }
        }
        for(auto &vec: cand1) {
            int x = vec[0], y = vec[1];
            // printf("try %d %d\n", x, y);
            vis.insert({x, y, 0});
            for(int d = 0; d < maxd; ++d)
                for(int ofs = -4; ofs <= 0; ++ofs) {
                    int px = x + dx[d] * ofs, py = y + dy[d] * ofs;
                    auto it = ctr.insert({{px, py, d}, {0, 0}}).first;
                    ++(it -> second)[0];
                    if((it -> second)[0] == 4 && !(it -> second)[1]) {
                        int qx = px, qy = py;
                        for(int i = 0; i < 5; ++i, qx += dx[d], qy += dy[d])
                            if(!vis.count({qx, qy, 0})) {
                                // printf("cand %d %d\n", qx, qy);
                                cand0.insert({qx, qy});
                            }
                    }
                }
            if(cand0.size() > 1)
                return "Black";
            cand0.clear();
            vis.erase({x, y, 0});
            for(int d = 0; d < maxd; ++d)
                for(int ofs = -4; ofs <= 0; ++ofs) {
                    int px = x + dx[d] * ofs, py = y + dy[d] * ofs;
                    auto it = ctr.insert({{px, py, d}, {0, 0}}).first;
                    --(it -> second)[0];
                }
        }
        return "None";
    }
};
