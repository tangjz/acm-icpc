class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int ans = 0, n = (int)arr.size();
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(abs(arr[i] - arr[j]) <= a)
                    for(int k = j + 1; k < n; ++k)
                        ans += abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c;
        return ans;
    }
};
