class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& seq) { // seq.size() >= 2
        int ox, oy, dx, dy, tx, ty;
        tie(ox, oy) = make_pair(seq[0][0], seq[0][1]);
        tie(dx, dy) = make_pair(seq[1][0] - ox, seq[1][1] - oy);
        for(auto &it : seq) {
            tie(tx, ty) = make_pair(it[0] - ox, it[1] - oy);
            if(tx * dy != ty * dx)
                return 0;
        }
        return 1;
    }
};
