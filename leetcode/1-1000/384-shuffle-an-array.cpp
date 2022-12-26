class Solution {
    mt19937_64 rnd;
    vector<int> seq;
public:
    Solution(vector<int>& nums) {
        rnd.seed(19260817);
        seq = move(nums);
    }

    vector<int> reset() {
        return seq;
    }

    vector<int> shuffle() {
        int n = seq.size();
        vector<int> ret = seq;
        for(int i = 0; i < n; ++i)
            swap(ret[i], ret[i + rnd() % (n - i)]);
        return move(ret);
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
