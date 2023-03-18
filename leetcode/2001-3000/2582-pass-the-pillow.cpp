class Solution {
public:
    int passThePillow(int n, int time) {
        time %= n + n - 2;
        return time < n ? time + 1 : n + n - time - 1;
    }
};
