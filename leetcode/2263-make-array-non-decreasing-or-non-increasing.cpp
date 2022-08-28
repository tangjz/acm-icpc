class Solution {
    int solve(vector<int> &nums) {
        int ans = 0;
        priority_queue<int> que;
        for(int x: nums) {
            if(!que.empty() && que.top() > x) {
                ans += que.top() - x;
                que.pop();
                que.push(x);
            }
            que.push(x);
        }
        return ans;
    }
public:
    int convertArray(vector<int>& nums) {
        int ans = solve(nums);
        reverse(nums.begin(), nums.end());
        return min(ans, solve(nums));
    }
};
