class Solution {
public:
    bool nimGame(vector<int>& piles) {
        int sg = 0;
        for(int x: piles)
            sg ^= x;
        return sg;
    }
};
