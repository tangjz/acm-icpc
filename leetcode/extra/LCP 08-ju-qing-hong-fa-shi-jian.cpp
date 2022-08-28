class Solution {
public:
    vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
        int n = increase.size();
        vector<vector<int> > seq(3, vector<int>(n + 1));
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < n; ++j)
                seq[i][j + 1] = seq[i][j] + increase[j][i];
        vector<int> ans;
        ans.reserve(requirements.size());
        for(auto &vec: requirements) {
            int upp = 0;
            for(int i = 0; i < 3; ++i)
                upp = max(upp, (int)(lower_bound(seq[i].begin(), seq[i].end(), vec[i]) - seq[i].begin()));
            ans.push_back(upp <= n ? upp : -1);
        }
        return ans;
    }
};
