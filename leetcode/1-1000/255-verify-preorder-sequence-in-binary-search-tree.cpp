class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int low = INT_MIN, tot = 0, n = preorder.size();
        for(int i = 0; i < n; ++i) {
            int x = preorder[i];
            if(x < low)
                return 0;
            for( ; tot && preorder[tot - 1] < x; low = max(low, preorder[--tot]));
            preorder[tot++] = x;
        }
        return 1;
    }
};
