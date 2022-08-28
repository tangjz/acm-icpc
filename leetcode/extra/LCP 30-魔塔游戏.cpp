class Solution {
public:
    int magicTower(vector<int>& nums) {
        if(accumulate(nums.begin(), nums.end(), 0LL) < 0)
            return -1;
        int cnt = 0;
        long long sum = 0;
        priority_queue<int> que;
        for(int x: nums) {
            que.push(-x);
            sum += x;
            if(sum < 0) {
                sum += que.top();
                que.pop();
                ++cnt;
            }
        }
        return cnt;
    }
};
