class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int cnt = 0;
        long long diff = 0;
        vector<int> sorted(arr.begin(), arr.end());
        sort(sorted.begin(), sorted.end());
        for(int i = 0; i < (int)arr.size(); ++i) {
            diff += arr[i] - sorted[i];
            cnt += !diff;
        }
        return cnt;
    }
};
