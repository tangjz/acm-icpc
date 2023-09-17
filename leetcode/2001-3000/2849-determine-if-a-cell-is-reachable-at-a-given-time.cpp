class Solution {
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        int dx = abs(sx - fx), dy = abs(sy - fy);
        if(dx > dy)
            swap(dx, dy);
        if(t < dy)
            return 0;
        return dx || dy ? 1 : t != 1;
    }
};
