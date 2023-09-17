class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> deg(numCourses, 0);
        vector<vector<int> > e(numCourses, vector<int>());
        for(auto &it : prerequisites) {
            ++deg[it[0]];
            e[it[1]].push_back(it[0]);
        }
        vector<int> que;
        for(int i = 0; i < numCourses; ++i)
            if(!deg[i])
                que.push_back(i);
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int &v : e[u])
                if(!(--deg[v]))
                    que.push_back(v);
        }
        return (int)que.size() == numCourses ? que : vector<int>();
    }
};
