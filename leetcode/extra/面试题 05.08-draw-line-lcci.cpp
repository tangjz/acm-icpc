class Solution {
public:
    vector<int> drawLine(int length, int w, int x1, int x2, int y) {
        vector<int> ret(length);
        int adt = w >> 5;
        int L = y * adt + (x1 >> 5), R = y * adt + (x2 >> 5);
        x1 &= 31;
        x2 &= 31;
        if(L < R) {
            ret[L] = ~0U >> x1;
            for(int i = L + 1; i < R && i < length; ++i)
                ret[i] = ~0U;
            ret[R] = ~0U ^ (x2 < 31 ? ~0U >> (x2 + 1) : 0);
        } else if(L < length) {
            ret[L] = (~0U >> x1) ^ (x2 < 31 ? ~0U >> (x2 + 1) : 0);
        }
        return ret;
    }
};
