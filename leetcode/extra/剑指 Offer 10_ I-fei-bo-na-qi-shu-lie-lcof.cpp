class Solution {
public:
    int fib(int n) {
        static const int mod = (int)1e9 + 7;
        int pre = 1, cur = 0;
        for(int i = 1; i <= n; ++i) {
            swap(pre, cur);
            (cur += pre) >= mod && (cur -= mod);
        }
        return cur;
    }
};
