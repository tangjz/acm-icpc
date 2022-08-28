class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int ans = INT_MAX;
        vector<int> que;
        for(int x : arr) {
            for(int &y : que)
                y &= x;
            que.push_back(x);
            que.erase(unique(que.begin(), que.end()), que.end());
            for(int y : que)
                ans = min(ans, abs(y - target));
        }
        return ans;
    }
};
