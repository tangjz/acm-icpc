class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size() / 3;
        vector<LL> suf(n * 3);
        priority_queue<int> que;
        LL cur = 0;
        for(int i = n * 3 - 1; i >= 0; --i) {
            cur += nums[i];
            que.push(-nums[i]);
            while(que.size() > n) {
                cur -= -que.top();
                que.pop();
            }
            suf[i] = cur;
        }
        while(!que.empty())
            que.pop();
        LL ans = LLONG_MAX;
        cur = 0;
        for(int i = 0; i < n * 2; ++i) {
            cur += nums[i];
            que.push(nums[i]);
            while(que.size() > n) {
                cur -= que.top();
                que.pop();
            }
            if(que.size() == n)
                ans = min(ans, cur - suf[i + 1]);
        }
        return ans;
    }
};
