class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits) {
        if(unordered_set<char>(suits.begin(), suits.end()).size() == 1)
            return "Flush";
        int upp = 0;
        unordered_map<int, int> ctr;
        for(int x: ranks)
            upp = max(upp, ++ctr[x]);
        if(upp >= 3)
            return "Three of a Kind";
        return upp == 2 ? "Pair" : "High Card";
    }
};
