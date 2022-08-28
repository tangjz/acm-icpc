class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        for(int i = 0; i + 1 < n; ++i) {
            int dt = arr[i] - arr[i + 1];
            arr[i] = (dt > 0) - (dt < 0);
        }
        int ans = 1;
        for(int i = 0; i + 1 < n; ++i) {
            if(!arr[i])
                continue;
            int j = i + 1;
            for( ; j + 1 < n && arr[j] == -arr[j - 1]; ++j);
            ans = max(ans, j - i + 1);
            i = j - 1;
        }
        return ans;
    }
};
