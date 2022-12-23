class Solution {
public:
    int lastMaterial(vector<int>& A) {
        priority_queue<int> que;
        for(int x: A)
            que.push(x);
        while(que.size() > 1) {
            int u = que.top();
            que.pop();
            u -= que.top();
            que.pop();
            if(u)
                que.push(u);
        }
        return que.empty() ? 0 : que.top();
    }
};
