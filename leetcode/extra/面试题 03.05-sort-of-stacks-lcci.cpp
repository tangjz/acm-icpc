class SortedStack {
    stack<int> main;
public:
    SortedStack() {
        stack<int>().swap(main);
    }
    
    void push(int val) {
        static stack<int> stk;
        for( ; !main.empty() && main.top() < val; stk.push(main.top()), main.pop());
        main.push(val);
        for( ; !stk.empty(); main.push(stk.top()), stk.pop());
    }
    
    void pop() {
        if(isEmpty())
            return;
        main.pop();
    }
    
    int peek() {
        if(isEmpty())
            return -1;
        return main.top();
    }
    
    bool isEmpty() {
        return main.empty();
    }
};

/**
 * Your SortedStack object will be instantiated and called as such:
 * SortedStack* obj = new SortedStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->isEmpty();
 */
