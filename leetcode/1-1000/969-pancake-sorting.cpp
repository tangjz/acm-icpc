class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        int n = arr.size();
        vector<int> ret;
        for(int i = n - 1, j; i >= 0; --i) {
            if(arr[i] == i + 1)
                continue;
            for(j = i - 1; j >= 0 && arr[j] != i + 1; --j);
            if(j > 0) {
                reverse(arr.begin(), arr.begin() + j + 1);
                ret.push_back(j + 1);
            }
            reverse(arr.begin(), arr.begin() + i + 1);
            ret.push_back(i + 1);
        }
        return ret;
    }
};
