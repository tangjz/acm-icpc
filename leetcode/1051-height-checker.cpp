class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> arr(heights.begin(), heights.end());
        sort(arr.begin(), arr.end());
        int pos = 0, ans = 0;
        for(int x: arr) {
            ans += x != heights[pos++];
        }
        return ans;
    }
};
