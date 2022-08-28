class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end(), greater<int>());
        arr.back() = 1;
        while(arr.size() > 1) {
            int x = arr.back();
            arr.pop_back();
            int &y = arr.back();
            y = min(y, x + 1);
        }
        return arr.back();
    }
};
