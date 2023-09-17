class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int L = 1, R = (int)arr.size() - 2;
        while(L < R) {
            int M = (L + R) >> 1;
            if(arr[M] > arr[M + 1]) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
