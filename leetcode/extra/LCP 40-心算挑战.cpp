class Solution {
public:
    int maxmiumScore(vector<int>& cards, int cnt) {
        int n = cards.size(), upp[2] = {INT_MAX, INT_MAX};
        int c = 0, s = 0;
        nth_element(cards.begin(), cards.end() - cnt, cards.end());
        while(cnt--) {
            int x = cards.back();
            cards.pop_back();
            int o = x & 1;
            c ^= o;
            s += x;
            upp[o] = min(upp[o], x);
        }
        if(!(c & 1))
            return s;
        int ans = 0;
        while(!cards.empty()) {
            int x = cards.back();
            cards.pop_back();
            int o = x & 1;
            if(upp[!o] < INT_MAX)
                ans = max(ans, s - upp[!o] + x);
        }
        return max(ans, 0);
    }
};
