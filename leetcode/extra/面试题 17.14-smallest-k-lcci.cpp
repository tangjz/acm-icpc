class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        nth_element(arr.begin(), arr.begin() + k, arr.end());
        arr.resize(k);
        return arr;
    }
};
