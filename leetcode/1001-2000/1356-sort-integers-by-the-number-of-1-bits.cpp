class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), [&](int const &u, int const &v) {
            int bu = __builtin_popcount(u);
            int bv = __builtin_popcount(v);
            return bu < bv || (bu == bv && u < v);
        });
        return arr;
    }
};
