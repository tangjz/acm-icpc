class Solution {
public:
    bool checkPowersOfThree(int n) {
        return n <= 1 || n % 3 != 2 && checkPowersOfThree(n / 3);
    }
};
