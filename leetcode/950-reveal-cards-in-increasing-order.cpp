class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        vector<int> ret(n);
        queue<int> que;
        sort(deck.begin(), deck.end());
        for(int i = 0; i < n; ++i)
            que.push(i);
        auto it = deck.begin();
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            ret[u] = *(it++);
            if(!que.empty()) {
                u = que.front();
                que.pop();
                que.push(u);
            }
        }
        return ret;
    }
};
