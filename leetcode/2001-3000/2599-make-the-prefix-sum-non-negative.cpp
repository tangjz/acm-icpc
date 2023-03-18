class Solution {
public:
    int makePrefSumNonNegative(vector<int>& nums) {
        int ans = 0;
        long long sum = 0;
        priority_queue<int> que;
        for(int x: nums) {
            sum += x;
            que.push(-x);
            while(sum < 0) {
                sum += que.top();
                que.pop();
                ++ans;
            }
        }
        return ans;
    }
};