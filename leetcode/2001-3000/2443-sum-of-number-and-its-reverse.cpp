class Solution {
public:
    bool sumOfNumberAndReverse(int num) {
        static const int maxv = (int)1e5 + 1;
        static vector<bool> vis(maxv);
        if(!vis[0]) {
            for(int i = 0, j; i < maxv; ++i) {
                static char buf[7];
                int len = sprintf(buf, "%d", i);
                reverse(buf, buf + len);
                sscanf(buf, "%d", &j);
                j += i;
                if(j < maxv)
                    vis[j] = 1;
            }
        }
        return vis[num];
    }
};
