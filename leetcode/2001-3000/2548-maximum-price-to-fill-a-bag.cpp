class Solution {
public:
    double maxPrice(vector<vector<int>>& items, int capacity) {
        sort(items.begin(), items.end(), [&](auto const &u, auto const &v) {
            return u[0] * v[1] < u[1] * v[0];
        });
        double ans = 0;
        while(!items.empty() && capacity > 0) {
            auto &u = items.back();
            int com = min(u[1], capacity);
            ans += u[0] * com / (double)u[1];
            capacity -= com;
            items.pop_back();
        }
        return capacity > 0 ? -1 : ans;
    }
};
