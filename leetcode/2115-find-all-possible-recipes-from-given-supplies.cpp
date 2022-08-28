class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, int> hs;
        for(auto &it: recipes)
            hs[it] = (int)hs.size();
        for(auto &it: supplies)
            hs[it] = (int)hs.size();
        int n = recipes.size();
        vector<int> deg(n);
        vector<vector<int> > e(n);
        vector<int> que;
        for(int i = 0; i < n; ++i) {
            for(auto &it: ingredients[i]) {
                if(!hs.count(it)) {
                    ++deg[i];
                    continue;
                }
                int j = hs[it];
                if(j < n) {
                    ++deg[i];
                    e[j].push_back(i);
                }
            }
            if(!deg[i])
                que.push_back(i);
        }
        vector<string> ret;
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int v: e[u]) {
                if(!(--deg[v])) {
                    que.push_back(v);
                }
            }
            ret.push_back(recipes[u]);
        }
        return ret;
    }
};
