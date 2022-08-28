class Solution {
public:
    vector<int> transformArray(vector<int>& arr) {
        int n = arr.size();
        vector<int> dt(n);
        for(bool upd = 1; upd; ) {
            upd = 0;
            for(int i = 1; i + 1 < n; ++i) {
                dt[i] = 0;
                dt[i] += arr[i - 1] > arr[i] && arr[i] < arr[i + 1];
                dt[i] -= arr[i - 1] < arr[i] && arr[i] > arr[i + 1];
                upd |= !!dt[i];
            }
            for(int i = 1; i + 1 < n; ++i)
                arr[i] += dt[i];
        }
        return arr;
    }
};
