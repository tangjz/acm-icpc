class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        long long ans = 0;
        map<pair<int, int>, int> Hash;
        for(auto &it: rectangles) {
            int u = it[0], v = it[1];
            int com = gcd(u, v);
            pair<int, int> tmp = {u / com, v / com};
            ans += Hash[tmp]++;
        }
        return ans;
    }
};
