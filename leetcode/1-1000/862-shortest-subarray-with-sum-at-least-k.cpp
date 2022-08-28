class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        // min(i - j | p[i] - p[j] >= k)
        int n = nums.size(), ans = n + 1;
        vector<long long> psum(n + 1);
        vector<int> que(n + 1);
        que.push_back(0);
        for(int i = 1, L = 0, R = 0; i <= n; ++i) {
            psum[i] = psum[i - 1] + nums[i - 1];
            while(L <= R && psum[que[R]] >= psum[i])
                --R;
            while(L <= R && psum[i] - psum[que[L]] >= k)
                ans = min(ans, i - que[L++]);
            que[++R] = i;
        }
        return ans <= n ? ans : -1;
    }
};
