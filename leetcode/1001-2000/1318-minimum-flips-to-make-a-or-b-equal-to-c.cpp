class Solution {
public:
    int minFlips(int a, int b, int c) {
        if(!a && !b && !c)
            return 0;
        int ret = minFlips(a >> 1, b >> 1, c >> 1);
        if(c & 1) {
            if(!(a & 1) && !(b & 1))
                ++ret;
        } else {
            ret += (a & 1) + (b & 1);
        }
        return ret;
    }
};
