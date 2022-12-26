class MyStack {
    queue<int> que;
public:
    MyStack() {
        queue<int>().swap(que);
    }

    void push(int x) {
        int n = que.size();
        que.push(x);
        while(n--) {
            x = que.front();
            que.pop();
            que.push(x);
        }
    }

    int pop() {
        int x = que.front();
        que.pop();
        return x;
    }

    int top() {
        return que.front();
    }

    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
