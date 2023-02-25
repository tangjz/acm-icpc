class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        typedef long long LL;
        LL ans = 0;
        priority_queue<int> que;
        for(int x: nums)
            que.push(x);
        while(k--) {
            int x = que.top();
            que.pop();
            ans += x;
            x = (x - 1) / 3 + 1;
            que.push(x);
        }
        return ans;
    }
};
