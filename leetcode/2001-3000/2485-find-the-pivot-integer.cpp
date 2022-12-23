class Solution {
public:
    int pivotInteger(int n) {
        int s = n * (n + 1) / 2;
        for(int i = 1; i <= n; ++i) {
            int vL = i * (i + 1) / 2, vR = s - i * (i - 1) / 2;
            if(vL == vR)
                return i;
        }
        return -1;
    }
};
