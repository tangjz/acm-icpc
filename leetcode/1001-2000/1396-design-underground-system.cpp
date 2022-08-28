class UndergroundSystem {
    typedef long long LL;
    map<string, int> pos;
    map<int, pair<int, int> > info;
    map<pair<int, int>, pair<LL, int> > ctr;
    int getID(string &cur) {
        auto it = pos.find(cur);
        if(it != pos.end())
            return it -> second;
        int id = pos.size();
        pos.insert(make_pair(cur, id));
        return id;
    }
public:
    UndergroundSystem() {
        map<string, int>().swap(pos);
        map<int, pair<int, int> >().swap(info);
        map<pair<int, int>, pair<LL, int> >().swap(ctr);
    }
        
    void checkIn(int id, string stationName, int t) {
        info[id] = make_pair(getID(stationName), t);
    }
    
    void checkOut(int id, string stationName, int t) {
        pair<int, int> pre = info[id], cur = make_pair(getID(stationName), t);
        auto &it = ctr[make_pair(pre.first, cur.first)];
        it.first += cur.second - pre.second;
        ++it.second;
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto &it = ctr[make_pair(getID(startStation), getID(endStation))];
        return (double)it.first / it.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
