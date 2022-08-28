class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int ans = 0, n = (int)arr.size();
        for(int i = 0; i < n; ++i) {
            int sum = 0;
            for(int j = i, k = 1; j < n; ++j, ++k) {
                sum += arr[j];
                if(k & 1)
                    ans += sum;
            }
        }
        return ans;
    }
};
