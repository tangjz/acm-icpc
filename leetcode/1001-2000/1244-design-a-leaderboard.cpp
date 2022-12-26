class Leaderboard {
    unordered_map<int, int> Hash;
public:
    Leaderboard() {
        Hash.clear();
    }

    void addScore(int playerId, int score) {
        Hash[playerId] += score;
    }

    int top(int K) {
        int n = Hash.size();
        if(n < K)
            return 0;
        vector<int> vals;
        vals.reserve(n);
        for(auto &it: Hash)
            vals.push_back(it.second);
        nth_element(vals.begin(), vals.begin() + (n - K), vals.end());
        int sum = 0;
        for(int i = 1; i <= K; ++i)
            sum += vals[n - i];
        return sum;
    }

    void reset(int playerId) {
        Hash.erase(playerId);
    }
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */
