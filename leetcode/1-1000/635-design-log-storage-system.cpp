class LogSystem {
    map<string, vector<int> > logs;
public:
    LogSystem() {
        logs.clear();
    }

    void put(int id, string timestamp) {
        logs[timestamp].push_back(id);
    }

    vector<int> retrieve(string start, string end, string granularity) {
        static const string pat[] = {"Year", "Month", "Day", "Hour", "Minute", "Second"};
        int pos = 0;
        for( ; granularity != pat[pos]; ++pos);
        int ctr = 0;
        for(char &ch: start) {
            if(ch == ':') {
                ++ctr;
                continue;
            }
            if(ctr > pos)
                ch = '0';
        }
        ctr = 0;
        for(char &ch: end) {
            if(ch == ':') {
                ++ctr;
                continue;
            }
            if(ctr > pos)
                ch = '9';
        }
        vector<int> ret;
        for(auto it = logs.lower_bound(start); it != logs.end() && it -> first <= end; ++it)
            ret.insert(ret.end(), (it -> second).begin(), (it -> second).end());
        return ret;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(start,end,granularity);
 */
