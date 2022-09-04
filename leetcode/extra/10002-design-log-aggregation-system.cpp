class LogAggregator {
    unordered_map<int, string> msg;
    vector<vector<int> > ms, sv;
public:
    LogAggregator(int machines, int services) {
        msg.clear();
        vector<vector<int> >(machines).swap(ms);
        vector<vector<int> >(services).swap(sv);
    }
    
    void pushLog(int logId, int machineId, int serviceId, string message) {
        msg[logId] = message;
        ms[machineId].push_back(logId);
        sv[serviceId].push_back(logId);
    }
    
    vector<int> getLogsFromMachine(int machineId) {
        return ms[machineId];
    }

    vector<int> getLogsOfService(int serviceId) {
        return sv[serviceId];
    }
    
    vector<string> search(int serviceId, string searchString) {
        vector<string> ret;
        for(int logId: sv[serviceId]) {
            string &txt = msg[logId];
            if(txt.find(searchString) != string::npos)
                ret.push_back(txt);
        }
        return ret;
    }
};

/**
 * Your LogAggregator object will be instantiated and called as such:
 * LogAggregator* obj = new LogAggregator(machines, services);
 * obj->pushLog(logId,machineId,serviceId,message);
 * vector<int> param_2 = obj->getLogsFromMachine(machineId);
 * vector<int> param_3 = obj->getLogsOfService(serviceId);
 * vector<string> param_4 = obj->search(serviceId,searchString);
 */
