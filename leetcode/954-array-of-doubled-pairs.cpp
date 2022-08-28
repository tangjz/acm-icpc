class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        sort(arr.begin(), arr.end(), [&](int const &u, int const &v) {
            int dt = abs(u) - abs(v);
            return dt < 0 || !dt && (u < v);
        });
        int n = arr.size();
        vector<bool> vis(n);
        for(int i = 0, j = 0; i < n; ++i) {
            if(vis[i])
                continue;
            for(j = max(j, i + 1); j < n && (vis[j] || abs(arr[j]) < abs(arr[i]) * 2 || (abs(arr[j]) == abs(arr[i]) * 2 && arr[j] < arr[i] * 2)); ++j);
            if(j < n && arr[j] == arr[i] * 2) {
                vis[i] = vis[j] = 1;
            } else {
                return 0;
            }
        }
        return 1;
    }
};
