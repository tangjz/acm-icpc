class Solution {
    unordered_map<int, int> Hash;
public:
    Solution() {
        Hash[0] = 0;
        Hash[1] = 1;
        Hash[2] = 2;
    }
    int minDays(int n) {
        auto it = Hash.find(n);
        if(it != Hash.end())
            return it -> second;
        return Hash[n] = min(minDays(n / 2) + n % 2 + 1, minDays(n / 3) + n % 3 + 1);
    }
};
