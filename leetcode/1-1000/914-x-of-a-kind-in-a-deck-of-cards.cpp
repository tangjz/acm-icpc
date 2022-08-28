class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        unordered_map<int, int> ctr;
        for(int x: deck)
            ++ctr[x];
        int com = 0;
        for(auto &it: ctr)
            com = gcd(com, it.second);
        return com > 1;
    }
};
