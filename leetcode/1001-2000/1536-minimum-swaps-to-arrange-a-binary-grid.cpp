class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = (int)grid.size();
        vector<int> que;
        for(auto &it : grid) {
            int cnt;
            for(cnt = 0; cnt < n - 1 && !it[n - 1 - cnt]; ++cnt);
            que.push_back(cnt);
        }
        int ans = 0;
        for(int i = 0, j; i < n; ++i) {
            for(j = i; j < n; ++j)
                if(que[j] >= n - 1 - i) {
                    ans += j - i;
                    rotate(que.begin() + i, que.begin() + j, que.begin() + (j + 1));
                    break;
                }
            if(j == n)
                return -1;
        }
        return ans;
    }
};
