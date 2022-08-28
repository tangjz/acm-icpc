class Solution {
public:
    int shortestWay(string A, string B) {
        int n = A.size(), m = B.size();
        int ans = 0, pos = 0;
        while(pos < m) {
            int las = pos;
            for(char ch: A)
                if(B[pos] == ch) {
                    if((++pos) == m)
                        break;
                }
            if(las == pos)
                return -1;
            ++ans;
        }
        return ans;
    }
};
