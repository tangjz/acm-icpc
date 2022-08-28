class TimeMap {
    unordered_map<string, vector<pair<int, string> > > Hash;
public:
    TimeMap() {
        Hash.clear();
    }
    
    void set(string key, string value, int timestamp) {
        Hash[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if(!Hash.count(key))
            return "";
        auto &it = Hash[key];
        auto jt = lower_bound(it.begin(), it.end(), make_pair(timestamp + 1, (string)""));
        return jt == it.begin() ? "" : (--jt) -> second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
