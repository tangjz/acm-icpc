class ThroneInheritance {
    int root;
    unordered_map<string, int> Hash;
    vector<string> name;
    vector<int> alive;
    vector<vector<int> > child;
    int getIndex(string &buf) {
        auto it = Hash.find(buf);
        if(it != Hash.end())
            return it -> second;
        int tot = (int)Hash.size();
        Hash.insert({buf, tot});
        name.push_back(buf);
        alive.push_back(1);
        child.push_back({});
        return tot;
    }
    void dfs(int u, vector<string> &ret) {
        if(alive[u])
            ret.push_back(name[u]);
        for(int v : child[u])
            dfs(v, ret);
    }
public:
    ThroneInheritance(string kingName) {
        unordered_map<string, int>().swap(Hash);
        vector<int>().swap(alive);
        vector<vector<int> >().swap(child);
        root = getIndex(kingName);
    }
    
    void birth(string parentName, string childName) {
        int par = getIndex(parentName), chd = getIndex(childName);
        child[par].push_back(chd);
    }
    
    void death(string name) {
        int cur = getIndex(name);
        alive[cur] = 0;
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> ret;
        dfs(root, ret);
        return ret;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
