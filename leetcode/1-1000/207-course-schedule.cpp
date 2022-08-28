class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> deg(numCourses, 0);
        vector<vector<int> > e(numCourses, vector<int>());
        for(auto &it : prerequisites) {
            ++deg[it[1]];
            e[it[0]].push_back(it[1]);
        }
        queue<int> que;
        for(int i = 0; i < numCourses; ++i)
            if(!deg[i])
                que.push(i);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int &v : e[u])
                if(!(--deg[v]))
                    que.push(v);
        }
        for(int i = 0; i < numCourses; ++i)
            if(deg[i] > 0)
                return 0;
        return 1;
    }
};
