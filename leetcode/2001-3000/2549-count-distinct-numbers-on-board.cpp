class Solution {
public:
    int distinctIntegers(int n) {
        unordered_set<int> sp;
        queue<int> que;
        auto upd = [&](int x) {
            if(sp.insert(x).second)
                que.push(x);
        };
        upd(n);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v = 2; v < u; ++v)
                if(u % v == 1)
                    upd(v);
        }
        return sp.size();
    }
};
