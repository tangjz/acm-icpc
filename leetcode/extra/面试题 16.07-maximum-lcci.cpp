class Solution {
public:
    int maximum(int a, int b) {
        long long dt = (long long)a - b;
        return a + dt * (dt >> 63);
    }
};
