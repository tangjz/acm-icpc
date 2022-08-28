class Solution {
public:
    int countVowelStrings(int n) {
        // binom(n + 4, 4)
        return (n + 4) * (n + 3) * (n + 2) * (n + 1) / 24;
    }
};
