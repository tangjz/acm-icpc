class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int ans = 0;
        unordered_map<int, int> ctr;
        for(auto &it: dominoes) {
            int u = it[0], v = it[1];
            if(u > v)
                swap(u, v);
            int x = u * 10 + v;
            ans += ctr[x]++;
        }
        return ans;
    }
};
