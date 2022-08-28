class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> psum(n + 1, 0), pre(n + 1, INT_MAX);
        unordered_map<int, int> pos;
        for(int i = 0; i < n; ++i) {
            psum[i + 1] = psum[i] + arr[i];
            pos[psum[i]] = i;
            auto it = pos.find(psum[i + 1] - target);
            if(it != pos.end())
                pre[i + 1] = i + 1 - (it -> second);
            pre[i + 1] = min(pre[i + 1], pre[i]);
        }
        int ans = INT_MAX;
        pos.clear();
        for(int i = n - 1; i >= 0; --i) {
            pos[psum[i + 1]] = i + 1;
            auto it = pos.find(psum[i] + target);
            if(it != pos.end() && pre[i] < INT_MAX)
                ans = min(ans, (it -> second) - i + pre[i]);
        }
        return ans < INT_MAX ? ans : -1;
    }
};
