class Solution {
public:
    string nextPalindrome(string num) {
        int n = num.size(), m = n / 2;
        if(!next_permutation(num.begin(), num.begin() + m))
            return "";
        for(int i = 0; i < m; ++i)
            num[n - 1 - i] = num[i];
        return num;
    }
};
