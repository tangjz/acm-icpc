class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        int pos = -1;
        vector<int> ord;
        for(auto &it : restaurants) {
            ++pos;
            if(it[2] < veganFriendly || it[3] > maxPrice || it[4] > maxDistance)
                continue;
            ord.push_back(pos);
        }
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            auto &it = restaurants[u], &jt = restaurants[v];
            int dif = it[1] - jt[1];
            return dif > 0 || (!dif && it[0] > jt[0]);
        });
        vector<int> ret;
        for(int id : ord)
            ret.push_back(restaurants[id][0]);
        return ret;
    }
};
