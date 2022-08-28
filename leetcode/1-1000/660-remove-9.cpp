class Solution {
public:
    int newInteger(int n) {
        return n ? newInteger(n / 9) * 10 + n % 9 : 0;
    }
};
