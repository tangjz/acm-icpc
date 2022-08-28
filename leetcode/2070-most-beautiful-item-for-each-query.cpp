class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        sort(items.begin(), items.end());
        vector<vector<int> > seq;
        seq.push_back({0, 0});
        for(auto &it: items) {
            if(seq.empty() || seq.back()[1] < it[1]) {
                seq.push_back(it);
                printf("%d %d\n", it[0], it[1]);
            }
        }
        vector<int> ans;
        for(int v: queries) {
            auto it = lower_bound(seq.begin(), seq.end(), vector<int>{v + 1, -1});
            ans.push_back((*(--it))[1]);
        }
        return ans;
    }
};
