class Solution {
public:
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_map<int, int> row, col, rc, cr;
        unordered_map<int, unordered_set<int> > sp;
        for(auto &it: lamps) {
            int x = it[0], y = it[1];
            auto &tp = sp[x];
            if(tp.count(y))
                continue;
            tp.insert(y);
            ++row[x];
            ++col[y];
            ++rc[x - y];
            ++cr[x + y];
        }
        vector<int> ret;
        for(auto &it: queries) {
            int x = it[0], y = it[1];
            ret.push_back(!row[x] && !col[y] && !rc[x - y] && !cr[x + y] ? 0 : 1);
            for(int dx = -1; dx <= 1; ++dx) {
                if(!sp.count(x + dx))
                    continue;
                int xx = x + dx;
                auto &tp = sp[xx];
                for(int dy = -1; dy <= 1; ++dy)
                    if(tp.count(y + dy)) {
                        int yy = y + dy;
                        // printf("erase %d %d\n", xx, yy);
                        tp.erase(yy);
                        --row[xx];
                        --col[yy];
                        --rc[xx - yy];
                        --cr[xx + yy];
                    }
                if(tp.empty())
                    sp.erase(xx);
            }
        }
        return ret;
    }
};
