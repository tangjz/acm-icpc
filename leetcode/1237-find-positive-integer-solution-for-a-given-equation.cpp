/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        const int maxd = (int)1e3 + 1;
        vector<vector<int> > ret;
        for(int x = 1, y = maxd - 1; x < maxd; ++x) {
            int his;
            for( ; y >= 1 && (his = customfunction.f(x, y)) > z; --y);
            if(y >= 1 && his == z)
                ret.push_back({x, y});
        }
        return ret;
    }
};
