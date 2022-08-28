class LFUCache {
    struct Block {
        int freq;
        unordered_map<int, list<pair<int, int> >::iterator> pos;
        list<pair<int, int> > lst;
        Block(int freq) {
            this -> freq = freq;
            unordered_map<int, list<pair<int, int> >::iterator>().swap(pos);
            list<pair<int, int> >().swap(lst);
        }
        bool empty() {
            return lst.empty();
        }
        int frontKey() {
            return lst.empty() ? -1 : lst.begin() -> first;
        }
        int get(int key) {
            auto it = pos.find(key);
            return it == pos.end() ? -1 : (it -> second) -> second;
        }
        void erase(int key) {
            auto it = pos.find(key);
            if(it != pos.end()) {
                lst.erase(it -> second);
                pos.erase(key);
            }
        }
        void append(int key, int value) {
            pos.insert({key, lst.insert(lst.end(), {key, value})});
        }
    } ;
    int upp;
    unordered_map<int, list<Block>::iterator> pos;
    list<Block> lst;
public:
    LFUCache(int capacity) {
        upp = capacity;
        unordered_map<int, list<Block>::iterator>().swap(pos);
        list<Block>().swap(lst);
    }
    
    int get(int key) {
        auto it = pos.find(key);
        if(it == pos.end())
            return -1;
        list<Block>::iterator jt = it -> second, kt = jt;
        int value = jt -> get(key);
        if((++kt) == lst.end() || (kt -> freq) != (jt -> freq) + 1)
            kt = lst.insert(kt, Block((jt -> freq) + 1));
        jt -> erase(key);
        if(jt -> empty())
            lst.erase(jt);
        kt -> append(key, value);
        pos[key] = kt;
        return value;
    }
    
    void put(int key, int value) {
        if(!upp)
            return;
        auto it = pos.find(key);
        if(it != pos.end()) {
            list<Block>::iterator jt = it -> second, kt = jt;
            if((++kt) == lst.end() || (kt -> freq) != (jt -> freq) + 1)
                kt = lst.insert(kt, Block((jt -> freq) + 1));
            jt -> erase(key);
            if(jt -> empty())
                lst.erase(jt);
            kt -> append(key, value);
            pos[key] = kt;
            return;
        }
        if((int)pos.size() == upp) {
            auto jt = lst.begin();
            int tmp = jt -> frontKey();
            jt -> erase(tmp);
            if(jt -> empty())
                lst.erase(jt);
            pos.erase(tmp);
        }
        list<Block>::iterator jt;
        if(lst.empty() || (lst.begin() -> freq) != 1) {
            jt = lst.insert(lst.begin(), Block(1));
        } else {
            jt = lst.begin();
        }
        jt -> append(key, value);
        pos[key] = jt;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
