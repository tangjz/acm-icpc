class MonitoringSystem {
    map<string, pair<vector<int>, map<string, vector<int> > > > appLtc;
    map<string, map<string, map<int, int> > > appErr;

public:
    MonitoringSystem() {

    }

    void logLatency(string applicationName, string api, int latencyInMills) {
        auto &[all, sub] = appLtc[applicationName];
        all.push_back(latencyInMills);
        sub[api].push_back(latencyInMills);
    }

    void logError(string applicationName, string api, int errorCode) {
        ++appErr[applicationName][api][errorCode];
    }

    int getPercentileLatency(int percentile, string applicationName, string api) {
        auto &[all, sub] = appLtc[applicationName];
        auto &vec = sub.count(api) ? sub[api] : all;
        sort(vec.begin(), vec.end());
        int idx = max(0, percentile * (int)vec.size() / 100 - 1);
        return vec[idx];
    }

    vector<int> getTopErrors(string applicationName, string api) {
        auto &sub = appErr[applicationName];
        vector<pair<int, int> > seq;
        if(sub.count(api) && sub[api].size() >= 3) {
            for(auto &it: sub[api])
                seq.push_back({-it.second, it.first});
        } else {
            for(auto &mp: sub)
                for(auto &it: mp.second)
                    seq.push_back({-it.second, it.first});
        }
        nth_element(seq.begin(), seq.begin() + 2, seq.end());
        seq.resize(3);
        sort(seq.begin(), seq.end());
        vector<int> ret;
        for(auto &it: seq)
            ret.push_back(it.second);
        return ret;
    }
};

/**
 * Your MonitoringSystem object will be instantiated and called as such:
 * MonitoringSystem* obj = new MonitoringSystem();
 * obj->logLatency(applicationName,api,latencyInMills);
 * obj->logError(applicationName,api,errorCode);
 * int param_3 = obj->getPercentileLatency(percentile,applicationName,api);
 * vector<int> param_4 = obj->getTopErrors(applicationName,api);
 */
