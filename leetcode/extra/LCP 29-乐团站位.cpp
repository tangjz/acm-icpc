class Solution {
public:
    int orchestraLayout(int num, int xPos, int yPos) {
        typedef long long LL;
        const int mod = 9;
        int pos = min(min(xPos, num - 1 - xPos), min(yPos, num - 1 - yPos));
        int dis = (num - pos) * 4LL * pos % mod;
        int L = pos, R = num - 1 - pos;
        if(xPos == L) {
            dis = (dis + yPos - L) % mod;
        } else {
            dis = (dis + R - L) % mod;
            if(yPos == R) {
                dis = (dis + xPos - L) % mod;
            } else {
                dis = (dis + R - L) % mod;
                if(xPos == R) {
                    dis = (dis + R - yPos) % mod;
                } else {
                    dis = (dis + R - L) % mod;
                    dis = (dis + R - xPos) % mod;
                }
            }
        }
        return dis + 1;
    }
};
