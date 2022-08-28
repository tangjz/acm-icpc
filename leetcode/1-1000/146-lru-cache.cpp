class LRUCache {
private:
    typedef list<pair<int, int> > List;
    typedef unordered_map<int, List::iterator> Map;
    int upp, tot;
    List que;
    Map pos;
public:
    LRUCache(int capacity) {
        upp = capacity;
        tot = 0;
        que.clear();
        pos.clear();
        pos.reserve(upp);
    }
    
    int get(int key) {
        int value = -1;
        Map::const_iterator it = pos.find(key);
        if(it != pos.end()) {
            List::iterator jt = it -> second;
            value = jt -> second;
            que.erase(jt);
            pos[key] = que.insert(que.end(), make_pair(key, value));
        }
        return value;
    }
    
    void put(int key, int value) {
        Map::const_iterator it = pos.find(key);
        if(it != pos.end()) {
            que.erase(it -> second);
            --tot;
        }
        if(tot == upp) {
            pos.erase(que.front().first);
            que.pop_front();
            --tot;
        }
        pos[key] = que.insert(que.end(), make_pair(key, value));
        ++tot;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
