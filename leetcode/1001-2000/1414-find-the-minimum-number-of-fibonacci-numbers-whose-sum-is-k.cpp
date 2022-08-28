class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        vector<int> fib;
        fib.push_back(1);
        fib.push_back(2);
        while(fib.back() <= k)
            fib.push_back(fib.back() + fib[(int)fib.size() - 2]);
        reverse(fib.begin(), fib.end());
        int cnt = 0;
        for(int x : fib)
            if(k >= x) {
                ++cnt;
                k -= x;
            }
        return cnt;
    }
};
