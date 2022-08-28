class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        int ans = 0;
        while(target > 1) {
            if(maxDoubles) {
                int nxt = target >> 1;
                ans += target - (nxt << 1) + 1;
                target = nxt;
                --maxDoubles;
                continue;
            }
            ans += target - 1;
            target = 1;
        }
        return ans;
    }
};
