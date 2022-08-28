class Solution {
public:
    bool isUgly(int n) {
        if(!n)
            return 0;
        for(int i = 2; i <= 5; ++i)
            for( ; n % i == 0; n /= i);
        return n == 1;
    }
};
