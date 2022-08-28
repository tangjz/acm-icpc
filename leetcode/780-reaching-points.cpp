class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while(sx <= tx && sy <= ty) {
            if(sx == tx && sy == ty)
                return 1;
            if(tx == ty)
                return 0;
            if(tx < ty) {
                swap(sx, sy);
                swap(tx, ty);
            }
            int d = (tx - sx) / ty;
            if(!d)
                return 0;
            tx -= d * ty;
        }
        return 0;
    }
};
