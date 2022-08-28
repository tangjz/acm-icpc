class MyHashMap {
    mt19937 rnd;
    int cap, sz;
    unsigned ofs;
    vector<list<pair<int, int> > > buckets;
    
    void refactor(int newCap) {
        vector<list<pair<int, int> > > newBuckets(newCap);
        ofs = rnd();
        for(auto &it: buckets)
            for(auto &jt: it) {
                int idx = ((unsigned)jt.first ^ ofs) & (newCap - 1);
                newBuckets[idx].push_back(move(jt));
            }
        buckets = move(newBuckets);
        cap = newCap;
    }
public:
    MyHashMap() {
        rnd.seed(19260817);
        cap = 1;
        sz = 0;
        ofs = rnd();
        buckets = {{}};
    }
    
    void put(int key, int value) {
        int idx = ((unsigned)key ^ ofs) & (cap - 1);
        bool found = false;
        for(auto &it: buckets[idx])
            if(it.first == key) {
                it.second = value;
                found = true;
                break;
            }
        if(!found) {
            buckets[idx].push_back(make_pair(key, value));
            ++sz;
        }
        if(sz == cap) {
            refactor(cap << 1);
        }
    }
    
    int get(int key) {
        int idx = ((unsigned)key ^ ofs) & (cap - 1);
        for(auto &it: buckets[idx])
            if(it.first == key) {
                return it.second;
            }
        return -1;
    }
    
    void remove(int key) {
        int idx = ((unsigned)key ^ ofs) & (cap - 1);
        bool found = false;
        for(auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it)
            if(it -> first == key) {
                --sz;
                buckets[idx].erase(it);
                found = true;
                break;
            }
        if(sz > 0 && sz + (sz >> 1) < cap) {
            refactor(cap >> 1);
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
