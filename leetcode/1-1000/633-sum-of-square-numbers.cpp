class Solution {
public:
    bool judgeSquareSum(int c) {
        typedef long long LL;
        int i = 0, j = 0;
        for( ; (LL)j * j < c; ++j);
        for( ; i <= j; ++i) {
            for( ; i <= j && (LL)i * i + (LL)j * j > c; --j);
            if(i <= j && (LL)i * i + (LL)j * j == c)
                return 1;
        }
        return 0;
    }
};
