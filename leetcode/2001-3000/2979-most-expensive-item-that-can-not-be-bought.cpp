class Solution {
public:
    int mostExpensiveItem(int primeOne, int primeTwo) {
        return (primeOne - 1) * (primeTwo - 1) - 1;
    }
};
