class AllOne {
    typedef pair<int, unordered_set<string> > Item;
    list<Item> lst;
    unordered_map<string, list<Item>::iterator> pos;
public:
    /** Initialize your data structure here. */
    AllOne() {
        list<Item>().swap(lst);
        unordered_map<string, list<Item>::iterator>().swap(pos);
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto it = pos.find(key);
        if(it == pos.end()) {
            list<Item>::iterator jt;
            if(lst.empty() || (lst.begin() -> first) != 1) {
                jt = lst.insert(lst.begin(), {1, {}});
            } else {
                jt = lst.begin();
            }
            (jt -> second).insert(key);
            pos[key] = jt;
        } else {
            list<Item>::iterator jt = it -> second, kt = jt;
            if((++kt) == lst.end() || (kt -> first) != (jt -> first) + 1)
                kt = lst.insert(kt, {(jt -> first) + 1, {}});
            (kt -> second).insert(key);
            pos[key] = kt;
            if((int)(jt -> second).size() > 1) {
                (jt -> second).erase(key);
            } else {
                lst.erase(jt);
            }
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        auto it = pos.find(key);
        if(it == pos.end())
            return;
        list<Item>::iterator jt = it -> second, kt = jt;
        if(jt -> first > 1) {
            if(jt == lst.begin() || ((--kt) -> first) != (jt -> first) - 1)
                kt = lst.insert(jt, {(jt -> first) - 1, {}});
            (kt -> second).insert(key);
            pos[key] = kt;
        } else {
            pos.erase(key);
        }
        if((int)(jt -> second).size() > 1) {
            (jt -> second).erase(key);
        } else {
            lst.erase(jt);
        }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return lst.empty() ? "" : *(lst.rbegin() -> second).begin();
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return lst.empty() ? "" : *(lst.begin() -> second).begin();
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
