class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int n = arr.size();
        if(n < 3)
            return 0;
        int pos = max_element(arr.begin() + 1, arr.end() - 1) - arr.begin();
        for(int i = 0; i < pos; ++i)
            if(arr[i] >= arr[i + 1])
                return 0;
        for(int i = pos + 1; i < n; ++i)
            if(arr[i - 1] <= arr[i])
                return 0;
        return 1;
    }
};
