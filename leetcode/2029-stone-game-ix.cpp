class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int ctr[3] = {};
        for(int x: stones)
            ++ctr[x % 3];
        ctr[0] &= 1;
        // printf("%d %d %d\n", ctr[0], ctr[1], ctr[2]);
        for(int i = 1; i < 3; ++i) {
            if(!ctr[i])
                continue;
            // printf("test %d: ", i);
            int len = 0, cur[3] = {};
            cur[i] = 1;
            ++len;
            // putchar('0' + i);
            if(ctr[0]) {
                cur[0] = 1;
                ++len;
                // putchar('0');
            }
            bool res = false;
            for(int j = i; cur[1] < ctr[1] || cur[2] < ctr[2]; j = 3 - j) {
                if(cur[j] == ctr[j]) {
                    res = len & 1;
                    break;
                }
                // putchar('0' + j);
                ++cur[j];
                ++len;
            }
            // printf(" : %d\n", res);
            if(res)
                return true;
        }
        return false;
    }
};
