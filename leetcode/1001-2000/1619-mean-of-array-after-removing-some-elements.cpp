class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int sum = 0, dt = n / 20;
        for(int i = dt; i + dt < n; ++i)
            sum += arr[i];
        return (double)sum / (n - dt - dt);
    }
};
