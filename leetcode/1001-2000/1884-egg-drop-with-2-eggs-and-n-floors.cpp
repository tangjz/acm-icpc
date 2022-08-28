class Solution {
public:
    int twoEggDrop(int n) {
        for(int i = 1; i <= n; ++i) {
            int best = i * (i + 1) / 2;
            if(n <= best)
                return i;
        }
        return -1;
    }
};
