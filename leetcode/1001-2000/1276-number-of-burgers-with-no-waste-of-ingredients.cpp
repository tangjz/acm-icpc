class Solution {
public:
    vector<int> numOfBurgers(int x, int y) {
        if(!(y * 2 <= x && x <= y * 4 && !(x & 1)))
            return {};
        int u = (x - y * 2) / 2, v = y - u;
        return {u, v};
    }
};
