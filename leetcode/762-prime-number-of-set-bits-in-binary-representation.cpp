class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        static const int maxd = 21;
        static const unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
        static int len, cnt, bits[maxd];
        len = cnt = 0;
        for(int i = left; i > 0; cnt += bits[len++] = i & 1, i >>= 1);
        bits[len] = 0;
        int ans = primes.count(cnt);
        for(int i = left + 1, j; i <= right; ++i) {
            for(j = 0; bits[j] == 1; bits[j++] = 0, --cnt);
            bits[j] = 1;
            ++cnt;
            if(j == len)
                bits[++len] = 0;
            ans += primes.count(cnt);
        }
        return ans;
    }
};
