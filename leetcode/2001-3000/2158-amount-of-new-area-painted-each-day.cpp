class Solution {
public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        int low = INT_MAX, upp = INT_MIN;
        for(auto &it: paint) {
            low = min(low, it[0]);
            upp = max(upp, it[1] + 1);
        }
        vector<int> ret, dsu(upp - low + 1, -1);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        for(auto &it: paint) {
            int cnt = 0;
            for(int i = dsuFind(it[0] - low); i < it[1] - low; i = dsuFind(i)) {
                ++cnt;
                dsu[i] = i + 1;
            }
            ret.push_back(cnt);
        }
        return ret;
    }
};
