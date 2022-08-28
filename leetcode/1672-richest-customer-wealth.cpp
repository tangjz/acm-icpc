class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int ans = 0;
        for(auto &it: accounts) {
            int sum = 0;
            for(int x: it)
                sum += x;
            ans = max(ans, sum);
        }
        return ans;
    }
};
