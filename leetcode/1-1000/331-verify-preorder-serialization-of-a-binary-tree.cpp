class Solution {
public:
    bool isValidSerialization(string preorder) {
        int rem = 1, n = preorder.size();
        for(int i = 0; i < n; ++i) {
            if((--rem) < 0)
                return 0;
            if(preorder[i] != '#')
                rem += 2;
            for( ; i < n && preorder[i] != ','; ++i);
        }
        return !rem;
    }
};
