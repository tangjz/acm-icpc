#include <cstdio>
#include <algorithm>
#include <unordered_map>

namespace int128_t {
    typedef unsigned long long ULL;
    const int BLEN = 40;
    const ULL BASE = (1ULL << BLEN) - 1; // [0, BASE]
    struct BigInt {
        ULL upp, low;
        BigInt() : upp(0), low(0) {}
        BigInt(int _low) : upp(0), low(_low) {}
        BigInt(ULL _upp, ULL _low) : upp(_upp), low(_low) {}
        bool operator == (BigInt const &t) const {
            return upp == t.upp && low == t.low;
        }
        BigInt operator + (BigInt const &t) const {
            BigInt ret = (BigInt){upp + t.upp, low + t.low};
            if(ret.low > BASE) {
                ++ret.upp;
                ret.low &= BASE;
            }
            return ret;
        }
        BigInt operator << (int const &t) const { // t = 1, 3
            BigInt ret = (BigInt){upp << t, low << t};
            if(ret.low > BASE) {
                ret.upp += ret.low >> BLEN;
                ret.low &= BASE;
            }
            return ret;
        }
        void operator *= (int const &t) { // t <= 61
            ULL res = low * t;
            low = res & BASE;
            upp = upp * t + (res >> BLEN);
        }
        BigInt operator / (int const &t) const { // t <= 61
            ULL res = (upp % t) << BLEN | low;
            return (BigInt){upp / t, res / t};
        }
        void operator /= (int const &t) { // t <= 10^6
            ULL res = (upp % t) << BLEN | low;
            upp /= t;
            low = res / t;
        }
        int operator % (int const &t) const {
            return (int)(((upp % t) << BLEN | low) % t);
        }
    };
}
using int128_t::BigInt;

namespace fastIO {
    #define BUF_SIZE 100000
    // fread -> read
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    template<class T> inline void read(T& x) {
        char ch;
        while(blank(ch = nc()));
        if(!IOerror)
            for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
    }
    // fwrite -> write
    struct Ostream_fwrite {
        char *buf, *p1, *pend;
        Ostream_fwrite() {
            buf = new char[BUF_SIZE];
            p1 = buf;
            pend = buf + BUF_SIZE;
        }
        void out(char ch) {
            if (p1 == pend) {
                fwrite(buf, 1, BUF_SIZE, stdout);
                p1 = buf;
            }
            *p1++ = ch;
        }
        void print(char *s) {
            for( ; *s; out(*s++));
        }
        void flush() {
            if(p1 != buf) {
                fwrite(buf, 1, p1 - buf, stdout);
                p1 = buf;
            }
        }
        ~Ostream_fwrite() {
            flush();
        }
    } Ostream;
    template<class T> inline void println(T const& x) {
        static char s[25];
        sprintf(s, "%.12f\n", (double)x);
        Ostream.print(s);
    }
    #undef BUF_SIZE
};

const int maxm = 19, pr[maxm] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
const int maxe = 80, maxs = 172513;
// const BigInt maxn = (BigInt)1e24;
namespace std {
    template<>
    struct hash<BigInt> {
        size_t operator () (BigInt const& key) const {
            return (size_t)key.upp ^ (size_t)key.low;
        }
    };
}
struct HashTable {
    int Counter;
    std::unordered_map<BigInt, int> Index;
    HashTable() : Counter(0), Index(std::unordered_map<BigInt, int>(maxs)) {
        newID(1);
    }
    bool count(BigInt const& key) const {
        return Index.count(key);
    }
    int getID(BigInt const& key) const {
        return Index.at(key);
    }
    int newID(BigInt const& key) {
        return Index[key] = Counter++;
    }
} Hash;
struct FracExp {
    int size, exp[maxm];
    int parse(BigInt val, int sz, int p[]) { // parse and calculate sigma(val)
        int sigma = 1;
        for(size = 0; size < sz; ++size) {
            for(exp[size] = 0; val % p[size] == 0; ++exp[size], val /= p[size]);
            sigma *= exp[size] + 1;
        }
        exp[size] = 0;
        std::sort(exp, exp + size, std::greater<int>());
        return sigma;
    }
    BigInt value() const { // get minimum represent
        BigInt ret = 1;
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < exp[i]; ++j)
                ret *= pr[i];
        return ret;
    }
} cur;
typedef double DB;
DB f[maxs], g[maxs][maxm];
int dfs(BigInt value, int sigma) { // dfs(cur)
    if(Hash.count(value))
        return Hash.getID(value);
    int cID = Hash.newID(value), pID;
    DB sum = 0;
    for(int i = 0, k = cur.size, j = k - 1; i < cur.size; ++i, --j) {
        if(cur.exp[j] != cur.exp[k]) { // different part
            k = j;
            int nxt = sigma - sigma / (cur.exp[k] + 1);
            if(!(--cur.exp[k]))
                --cur.size;
            pID = dfs(value / pr[k], nxt);
            if(!(cur.exp[k]++))
                ++cur.size;
        }
        int o = i - (cur.exp[k] == 1);
        g[cID][i] = (sum += o < 0 ? f[pID] : g[pID][o]);
    }
    f[cID] = (sigma + sum) / (sigma - 1);
    for(int i = 0; i < cur.size; ++i)
        g[cID][i] += f[cID];
    return cID;
}
int main() {
    BigInt n;
    int m, p[maxm]; // p[i] <= 10^6
    char buf[1 << 5 | 1];
    using namespace fastIO;
    for(int Case = 1; read(n), read(m), !IOerror; ++Case) {
        for(int i = 0; i < m; ++i)
            read(p[i]);
        int sigma = cur.parse(n, m, p);
        sprintf(buf, "Case #%d: ", Case);
        Ostream.print(buf);
        println(f[dfs(cur.value(), sigma)]);
    }
    return 0;
}
