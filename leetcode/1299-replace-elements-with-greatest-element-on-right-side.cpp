class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = (int)arr.size(), upp = -1;
        for(int i = n - 1; i >= 0; --i) {
            arr[i] = max(arr[i], upp);
            swap(arr[i], upp);
        }
        return arr;
    }
};
