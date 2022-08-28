class ConsistentHashing {
    map<int, set<int> > vals;
    vector<pair<set<int>, bool> > nodes;
public:
    ConsistentHashing(int initialNodes) {
        vals.clear();
        nodes.clear();
        nodes.resize(initialNodes + 1);
    }

    int getNodeForKey(int key) {
        if(!vals[key].empty()) {
            int x = *vals[key].begin();
            assert(!nodes[x].second);
            assert(nodes[x].first.count(key));
            return x;
        }
        int low = -1;
        for(int i = 1; i < nodes.size(); ++i)
            if(!nodes[i].second && (low == -1 || nodes[i].first.size() < nodes[low].first.size()))
                low = i;
        assert(low != -1 && !nodes[low].second);
        nodes[low].first.insert(key);
        vals[key].insert(low);
        return low;
    }
    
    int removeNode(int node) {
        int low = -1;
        for(int i = 1; i < nodes.size(); ++i)
            if(i != node && !nodes[i].second && (low == -1 || nodes[i].first.size() < nodes[low].first.size()))
                low = i;
        assert(low != -1 && low != node && !nodes[low].second);
        for(int x: nodes[node].first) {
            vals[x].erase(node);
            if(nodes[low].first.insert(x).second)
                vals[x].insert(low);
        }
        nodes[node].first.clear();
        nodes[node].second = 1;
        return low;
    }
    
    vector<int> addNode() {
        int low = -1;
        for(int i = 1; i < nodes.size(); ++i)
            if(!nodes[i].second && (low == -1 || nodes[i].first.size() < nodes[low].first.size()))
                low = i;
        assert(low != -1 && !nodes[low].second);
        int idx = nodes.size();
        nodes.push_back({});
        for(int x: nodes[low].first) {
            nodes[idx].first.insert(x);
            vals[x].insert(idx);
        }
        return {idx, low};
    }

    vector<int> getKeysInNode(int node) {
        assert(!nodes[node].second);
        vector<int> ret;
        for(int x: nodes[node].first)
            ret.push_back(x);
        return ret;
    }
};
