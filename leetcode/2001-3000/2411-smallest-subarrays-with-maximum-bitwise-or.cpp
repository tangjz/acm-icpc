class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size(), cur = 0, pre = 1;
        vector<int> ans(n);
        vector<pair<int, int> > que[2];
        for(int i = n - 1; i >= 0; --i) {
            swap(cur, pre);
            que[cur].clear();
            que[cur].push_back({nums[i], i});
            int las = nums[i];
            for(auto &it: que[pre]) {
                int nxt = las | it.first;
                if(nxt == las)
                    continue;
                que[cur].push_back({nxt, it.second});
                las = nxt;
            }
            ans[i] = que[cur].back().second - i + 1;
        }
        return ans;
    }
};
