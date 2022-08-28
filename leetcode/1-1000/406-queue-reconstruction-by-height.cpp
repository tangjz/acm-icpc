class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [&](auto const &u, auto const &v) {
            return u[0] < v[0] || (u[0] == v[0] && u[1] > v[1]);
        });
        vector<vector<int> > ret;
        while(!people.empty()) {
            vector<int> cur = move(people.back());
            people.pop_back();
            ret.insert(ret.begin() + cur[1], cur);
        }
        return ret;
    }
};
