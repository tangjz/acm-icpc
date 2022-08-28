class Solution {
public:
    int smallestFactorization(int num) {
        if(num == 1)
            return 1;
        long long ans = 0, pw = 1;
        for(int i = 9; i >= 2; --i)
            while(num % i == 0) {
                ans += i * pw;
                if(ans > INT_MAX)
                    return 0;
                pw *= 10;
                num /= i;
            }
        return num > 1 ? 0 : ans;
    }
};
