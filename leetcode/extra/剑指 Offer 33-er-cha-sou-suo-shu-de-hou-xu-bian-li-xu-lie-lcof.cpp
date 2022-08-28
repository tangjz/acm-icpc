class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        int n = postorder.size(), upp = INT_MAX;
        stack<int> stk;
        for(int i = n - 1; i >= 0; --i) {
            int x = postorder[i];
            if(x > upp)
                return 0;
            while(!stk.empty() && stk.top() > x) {
                upp = min(upp, stk.top());
                stk.pop();
            }
            stk.push(x);
        }
        return 1;
    }
};
