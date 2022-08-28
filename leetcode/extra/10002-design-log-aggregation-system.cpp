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
