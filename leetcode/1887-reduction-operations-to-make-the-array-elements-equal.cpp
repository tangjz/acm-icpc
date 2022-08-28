class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        vector<int> que = nums;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int ans = 0;
        for(int x: nums) {
            ans += lower_bound(que.begin(), que.end(), x) - que.begin();
        }
        return ans;
    }
};
