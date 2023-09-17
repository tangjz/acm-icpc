class Solution {
public:
    int distMoney(int a, int b) {
        if(a == b * 8)
            return b;
        if(a == b * 8 - 4)
            return b - 2;
        return a < b ? -1 : min((a - b) / 7, b - 1);
    }
};
