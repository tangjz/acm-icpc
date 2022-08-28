class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size(), f[2] = {1, 0}, ans = 0;
        for(int i = 1; i < n; ++i) {
            int g[2] = {1, 0};
            if(arr[i - 1] < arr[i])
                g[0] = max(g[0], f[0] + 1);
            if(f[0] > 1)
                f[1] = max(f[0], f[1]);
            if(f[1] > 1 && arr[i - 1] > arr[i])
                g[1] = max(g[1], f[1] + 1);
            f[0] = g[0];
            f[1] = g[1];
            ans = max(ans, f[1]);
        }
        return ans;
    }
};
