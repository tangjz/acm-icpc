class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        map<int, int> Hash;
        for(auto &it: logs)
            for(int i = it[0]; i < it[1]; ++i)
                ++Hash[i];
        pair<int, int> ans = *Hash.begin();
        swap(ans.first, ans.second);
        ans.second = -ans.second;
        for(auto &it: Hash) {
            pair<int, int> tmp = {it.second, -it.first};
            ans = max(ans, tmp);
        }
        return -ans.second;
    }
};
