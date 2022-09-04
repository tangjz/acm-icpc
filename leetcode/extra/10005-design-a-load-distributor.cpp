class DCLoadBalancer {
    // app: id -> {load use, {timestamp, machine id}}
    // machine: id -> {remain cap, ordered {timestamp, app id}}
    // heap: {max(machine remain cap), min(machine id)}

    int timestamp;
    map<int, pair<int, pair<int, int> > > app;
    map<int, pair<int, set<pair<int, int> > > > host;
    set<pair<int, int> > cand;

public:
    DCLoadBalancer() {
    }

    void addMachine(int machineId, int capacity) {
        host[machineId] = {capacity, {}};
        cand.insert({capacity, -machineId});
    }

    void removeMachine(int machineId) {
        if(!host.count(machineId))
            return;
        set<pair<int, int> > rem = move(host[machineId].second);
        cand.erase({host[machineId].first, -machineId});
        host.erase(machineId);
        bool bad = 0;
        for(auto &it: rem) {
            int appId = it.second;
            if(bad) {
                app.erase(appId);
            } else {
                int newMachineId = addApplication(appId, app[appId].first);
                if(newMachineId == -1)
                    app.erase(appId);
            }
        }
    }

    int addApplication(int appId, int loadUse) {
        if(cand.empty() || cand.rbegin() -> first < loadUse)
            return -1;
        int machineId = -(cand.rbegin() -> second);
        auto &[cap, rem] = host[machineId];
        cand.erase({cap, -machineId});
        app[appId] = {loadUse, {++timestamp, machineId}};
        rem.insert({timestamp, appId});
        cap -= loadUse;
        if(cap > 0)
            cand.insert({cap, -machineId});
        return machineId;
    }

    void stopApplication(int appId) {
        if(!app.count(appId))
            return;
        int loadUse = app[appId].first, timestamp, machineId;
        tie(timestamp, machineId) = app[appId].second;
        auto &[cap, rem] = host[machineId];
        if(cap > 0)
            cand.erase({cap, -machineId});
        rem.erase({timestamp, appId});
        cap += loadUse;
        cand.insert({cap, -machineId});
        app.erase(appId);
    }
    
    vector<int> getApplications(int machineId) {
        vector<int> ret;
        if(!host.count(machineId))
            return ret;
        static const int maxd = 10;
        for(auto &it: host[machineId].second) {
            ret.push_back(it.second);
            if(ret.size() == maxd)
                break;
        }
        return ret;
    }
};

/**
 * Your DCLoadBalancer object will be instantiated and called as such:
 * DCLoadBalancer* obj = new DCLoadBalancer();
 * obj->addMachine(machineId,capacity);
 * obj->removeMachine(machineId);
 * int param_3 = obj->addApplication(appId,loadUse);
 * obj->stopApplication(appId);
 * vector<int> param_5 = obj->getApplications(machineId);
 */
