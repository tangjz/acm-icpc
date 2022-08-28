class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = arr.size();
        for(int i = n - 1, low = INT_MAX; i >= 0; --i) {
            if(arr[i] > low) {
                int k = -1;
                for(int j = i + 1; j < n; ++j)
                    if(arr[j] < arr[i] && (k == -1 || arr[k] < arr[j]))
                        k = j;
                swap(arr[i], arr[k]);
                break;
            }
            low = min(low, arr[i]);
        }
        return move(arr);
    }
};
