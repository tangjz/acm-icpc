class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        int n = routes.size();
        unordered_map<int, vector<int> > sp;
        for(int i = 0; i < n; ++i)
            for(int x: routes[i])
                sp[x].push_back(i);
        unordered_map<int, int> dis;
        vector<int> rDis(n, -1);
        queue<int> rQue;
        auto upd = [&](int x, int d) {
            if(dis.count(x))
                return;
            dis[x] = d;
            for(int i: sp[x]) {
                if(rDis[i] != -1)
                    continue;
                rDis[i] = d;
                rQue.push(i);
            }
        };
        upd(target, 0);
        while(!rQue.empty() && !dis.count(source)) {
            int i = rQue.front();
            rQue.pop();
            for(int x: routes[i])
                upd(x, rDis[i] + 1);
        }
        return dis.count(source) ? dis[source] : -1;
    }
};
