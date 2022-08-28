class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int c[2] = {}, pos = 0;
        unordered_map<int, int> occ[2];
        for(int x: nums) {
            ++c[pos];
            ++occ[pos][x];
            pos = !pos;
        }
        pair<int, int> best[2] = {};
        for(auto &it: occ[1]) {
            pair<int, int> tmp = {it.second, it.first};
            if(tmp > best[0])
                swap(tmp, best[0]);
            if(tmp > best[1])
                swap(tmp, best[1]);
        }
        int ans = c[0] + c[1] - best[0].first;
        for(auto &it: occ[0]) {
            int o = it.first == best[0].second;
            ans = min(ans, c[0] - it.second + c[1] - best[o].first);
        }
        return ans;
    }
};
