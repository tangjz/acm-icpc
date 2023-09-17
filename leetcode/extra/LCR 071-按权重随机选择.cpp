class Solution {
    typedef pair<int, int> Node;
    typedef pair<Node, int> Item;
    int N, M;
    vector<Item> seq;
    mt19937 rnd;
public:
    Solution(vector<int>& w) {
        M = 0;
        for(int x : w)
            M += x;
        N = (int)w.size();
        queue<Node> lft, rht;
        int pos = 0;
        for(int x : w) {
            int y = x * N;
            queue<Node> &que = y < M ? lft : rht;
            que.push({pos++, y});
        }
        vector<Item>().swap(seq);
        seq.reserve(N);
        for(int i = 0; i < N; ++i) {
            Node u, v;
            if(lft.empty()) {
                u = {-1, 0};
            } else {
                u = lft.front();
                lft.pop();
            }
            assert(!rht.empty());
            v = rht.front();
            rht.pop();
            seq.push_back({u, v.first});
            if((v.second -= M - u.second) > 0) {
                queue<Node> &que = v.second < M ? lft : rht;
                que.push(v);
            }
        }
        assert(lft.empty() && rht.empty());
        rnd.seed(time(NULL));
    }

    int pickIndex() {
        Item &cur = seq[rnd() % N];
        return rnd() % M < cur.first.second ? cur.first.first : cur.second;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
