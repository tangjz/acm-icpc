class Solution {
public:
    bool isPerfectSquare(int num) {
        unsigned int x = 0, x2 = 0;
        while(x2 < num)
            x2 += (x++) << 1 | 1;
        return x2 == num;
    }
};
