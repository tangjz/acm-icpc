class Solution {
public:
    int halveArray(vector<int>& nums) {
        double sum = 0;
        priority_queue<double> que;
        for(int x: nums) {
            sum += x;
            que.push((double)x);
        }
        sum /= 2;
        int ans = 0;
        while(sum > 0) {
            ++ans;
            double x = que.top();
            que.pop();
            x /= 2;
            sum -= x;
            que.push(x);
        }
        return ans;
    }
};
