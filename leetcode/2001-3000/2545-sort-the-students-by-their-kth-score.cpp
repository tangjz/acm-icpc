class Solution {
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {
        sort(score.begin(), score.end(), [&](auto const &u, auto const &v) {
            return u[k] > v[k];
        });
        return score;
    }
};
