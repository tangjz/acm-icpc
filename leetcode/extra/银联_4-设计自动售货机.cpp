class VendingMachine {
    struct Items {
        int total;
        map<pair<int, int>, int> rem;
        set<pair<int, int> > expire;
    };
    unordered_map<string, int> user;
    unordered_map<string, Items> good;
public:
    VendingMachine() {

    }
    
    void addItem(int time, int number, string item, int price, int duration) {
        auto &sp = good[item];
        time += duration;
        sp.total += number;
        sp.rem[{price, time}] += number;
        sp.expire.insert({time, price});
        // printf("add %s %d %d %d\n", item.c_str(), price, time, number);
    }
    
    long long sell(int time, string customer, string item, int number) {
        auto &sp = good[item];
        auto &rem = sp.rem;
        auto &expire = sp.expire;
        while(!expire.empty() && expire.begin() -> first < time) {
            pair<int, int> cur = *expire.begin();
            expire.erase(cur);
            swap(cur.first, cur.second);
            // printf("expire %s %d %d %d\n", item.c_str(), cur.first, cur.second, rem[cur]);
            sp.total -= rem[cur];
            rem.erase(cur);
        }
        if(sp.total < number)
            return -1;
        typedef long long LL;
        LL ans = 0;
        while(number > 0) {
            pair<int, int> cur;
            int cnt;
            tie(cur, cnt) = *rem.begin();
            if(number < cnt) {
                // printf("partial sold %s %d %d %d\n", item.c_str(), cur.first, cur.second, number);
                sp.total -= number;
                ans += (LL)cur.first * number;
                rem[cur] -= number;
                break;
            }
            // printf("sold %s %d %d %d\n", item.c_str(), cur.first, cur.second, cnt);
            sp.total -= cnt;
            ans += (LL)cur.first * cnt;
            number -= cnt;
            rem.erase(cur);
            swap(cur.first, cur.second);
            expire.erase(cur);
        }
        int discount = min(user[customer]++, 30);
        ans = (ans * (100 - discount) - 1) / 100 + 1;
        return ans;
    }
};

/**
 * Your VendingMachine object will be instantiated and called as such:
 * VendingMachine* obj = new VendingMachine();
 * obj->addItem(time,number,item,price,duration);
 * long long param_2 = obj->sell(time,customer,item,number);
 */
