class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        auto calc = [&](vector<int> &seq) {
            int ret = 0, las[2] = {}, o = 0;
            for(int x: seq) {
                ret += x + x * (las[0] == 10 || las[1] == 10);
                las[o] = x;
                o = !o;
            }
            return ret;
        };
        int dt = calc(player1) - calc(player2);
        return dt > 0 ? 1 : (dt < 0 ? 2 : 0);
    }
};
