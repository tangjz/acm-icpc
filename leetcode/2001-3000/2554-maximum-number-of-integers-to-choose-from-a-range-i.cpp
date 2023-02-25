class Solution {
public:
    int maxCount(vector<int>& ban, int n, int upp) {
        sort(ban.begin(), ban.end());
        ban.erase(unique(ban.begin(), ban.end()), ban.end());
        int ans = 0, m = ban.size();
        for(int i = 1, j = 0; i <= n && i <= upp; ++i) {
            if(j < m && ban[j] == i) {
                ++j;
                continue;
            }
            ++ans;
            upp -= i;
        }
        return ans;
    }
};
