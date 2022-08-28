class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int ans = arr[1] - arr[0];
        for(int i = 2; i < n; ++i)
            ans = min(ans, arr[i] - arr[i - 1]);
        vector<vector<int> > ret;
        for(int i = 1; i < n; ++i)
            if(ans == arr[i] - arr[i - 1])
                ret.push_back({arr[i - 1], arr[i]});
        return ret;
    }
};
