class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int ans = 0;
        priority_queue<int> que;
        for(int x: nums) {
            ans += x;
            que.push(-x);
        }
        while(k--) {
            int x = -que.top();
            que.pop();
            ans += -x * 2;
            que.push(x);
        }
        return ans;
    }
};
