class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        priority_queue<int> que;
        for(int x: sticks)
            que.push(-x);
        int ans = 0;
        while(que.size() > 1) {
            int u = que.top();
            que.pop();
            int v = que.top();
            que.pop();
            u += v;
            ans -= u;
            que.push(u);
        }
        return ans;
    }
};
