class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> que;
        for(int x: stones)
            que.push(x);
        while(que.size() > 1) {
            int x = que.top();
            que.pop();
            x -= que.top();
            que.pop();
            if(x > 0)
                que.push(x);
        }
        return que.empty() ? 0 : que.top();
    }
};
