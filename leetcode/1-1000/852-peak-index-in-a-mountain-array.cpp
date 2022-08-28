class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size(), L = 0, R = n - 1;
        while(L < R) {
            int M = (L + R) >> 1;
            if(arr[M] < arr[M + 1]) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
