class Solution {
public:
    bool judgeCircle(string moves) {
        unordered_map<char, int> ctr;
        for(char ch: moves)
            ++ctr[ch];
        return ctr['L'] == ctr['R'] && ctr['U'] == ctr['D'];
    }
};
