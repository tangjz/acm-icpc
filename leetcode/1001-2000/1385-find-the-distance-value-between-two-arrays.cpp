class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
        for(int x : arr1) {
            int low = INT_MAX;
            for(int y : arr2)
                low = min(low, abs(x - y));
            ans += low > d;
        }
        return ans;
    }
};
