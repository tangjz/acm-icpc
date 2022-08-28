class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = (int)arr.size();
        sort(arr.begin(), arr.end());
        int med = arr[(n - 1) >> 1];
        sort(arr.begin(), arr.end(), [&](int const &u, int const &v) {
            int diff = abs(u - med) - abs(v - med);
            return diff > 0 || (!diff && u > v);
        });
        arr.resize(k);
        return arr;
    }
};
