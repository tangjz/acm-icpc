class Solution {
public:
    int fib(int n) {
        int pre = 1, cur = 0;
        for(int i = 1; i <= n; ++i) {
            swap(pre, cur);
            cur += pre;
        }
        return cur;
    }
};
