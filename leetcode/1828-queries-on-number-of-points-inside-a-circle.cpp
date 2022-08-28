class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> ans;
        for(auto &it: queries) {
            int cnt = 0;
            auto sqr = [](int x) {
                return x * x;
            };
            for(auto &jt: points) {
                if(sqr(it[0] - jt[0]) + sqr(it[1] - jt[1]) <= sqr(it[2]))
                    ++cnt;
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};
